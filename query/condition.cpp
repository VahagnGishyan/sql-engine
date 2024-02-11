
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "condition.hpp"

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <numeric>
#include <set>

// #include "database/database.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using Interface::UDynamicValue;

    namespace
    {
        using Query::UCondition;

        class Condition : public Query::ICondition
        {
           public:
            virtual auto Apply(const Interface::ITable& table) const
                -> Interface::RowIndexes
            {
                auto indexes = Interface::CreateRowIndexes(table.RowsCount());
                Apply(table, indexes);
                return indexes;
            }

           public:
            virtual void Apply(const Interface::ITable&,
                               Interface::RowIndexes& indexes) const = 0;
        };

        class And : public Condition
        {
           public:
            using ICondition::Check;

           public:
            And(UCondition left, UCondition right) :
                m_left{std::move(left)}, m_right{std::move(right)}
            {
            }

           public:
            static auto Create(UCondition left, UCondition right) -> UCondition
            {
                return std::make_unique<And>(std::move(left), std::move(right));
            }
            auto Copy() const -> UCondition override
            {
                return std::make_unique<And>(m_left->Copy(), m_right->Copy());
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                return (m_left->Check(value) && m_right->Check(value));
            }
            void Apply(const Interface::ITable& table,
                       Interface::RowIndexes& indexes) const override final
            {
                auto cyleft  = m_left->Apply(table);
                auto cyright = m_right->Apply(table);

                indexes = CreateIntersectionVector(cyleft, cyright);
            }

            auto ToString() const -> const std::string override
            {
                return fmt::format("And ({}, {})", m_left->ToString(),
                                   m_right->ToString());
            }

           protected:
            auto CreateIntersectionVector(const Interface::RowIndexes& cyleft,
                                          const Interface::RowIndexes& cyright)
                const -> Interface::RowIndexes
            {
                Interface::RowIndexes vector3;

                // Sort vectors for efficient intersection
                Interface::RowIndexes sortedVector1 = cyleft;
                Interface::RowIndexes sortedVector2 = cyright;
                std::sort(sortedVector1.begin(), sortedVector1.end());
                std::sort(sortedVector2.begin(), sortedVector2.end());

                // Use std::set_intersection to find common elements
                std::set_intersection(
                    sortedVector1.begin(), sortedVector1.end(),
                    sortedVector2.begin(), sortedVector2.end(),
                    std::back_inserter(vector3));

                return vector3;
            }

           protected:
            UCondition m_left;
            UCondition m_right;
        };

        //////////////////////////////////////////////////////////////////////

        class Or : public Condition
        {
           public:
            Or(UCondition left, UCondition right) :
                m_left{std::move(left)}, m_right{std::move(right)}
            {
            }

           public:
            static auto Create(UCondition left, UCondition right) -> UCondition
            {
                return std::make_unique<Or>(std::move(left), std::move(right));
            }
            auto Copy() const -> UCondition override
            {
                return std::make_unique<Or>(m_left->Copy(), m_right->Copy());
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                return (m_left->Check(value) || m_right->Check(value));
            }
            void Apply(const Interface::ITable& table,
                       Interface::RowIndexes& indexes) const override final
            {
                auto cyleft  = m_left->Apply(table);
                auto cyright = m_right->Apply(table);
                indexes      = MergeAndSort(cyleft, cyright);
            }

           public:
            auto ToString() const -> const std::string override
            {
                return fmt::format("Or ({},  {})", m_left->ToString(),
                                   m_right->ToString());
            }

           private:
            auto MergeAndSort(const Interface::RowIndexes& first,
                              const Interface::RowIndexes& second) const
                -> Interface::RowIndexes
            {
                // Create a set to store unique elements
                std::set<int> uniqueSet;

                // Insert elements from the first vector
                uniqueSet.insert(first.begin(), first.end());

                // Insert elements from the second vector
                uniqueSet.insert(second.begin(), second.end());

                // Copy elements from the set to a new vector
                Interface::RowIndexes result(uniqueSet.begin(),
                                             uniqueSet.end());

                // Sort the result vector
                std::sort(result.begin(), result.end());

                return result;
            }

           protected:
            UCondition m_left;
            UCondition m_right;
        };

        //////////////////////////////////////////////////////////////////////

        class Not : public Condition
        {
           public:
            Not(UCondition condition) : m_condition{std::move(condition)}
            {
            }

           public:
            static auto Create(UCondition condition) -> UCondition
            {
                return std::make_unique<Not>(std::move(condition));
            }
            auto Copy() const -> UCondition override
            {
                return std::make_unique<Not>(m_condition->Copy());
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                return !(m_condition->Check(value));
            }
            void Apply(const Interface::ITable& table,
                       Interface::RowIndexes& indexes) const override final
            {
                auto falseResults = m_condition->Apply(table);
                RemoveElementsInSecond(indexes, falseResults);
            }

           private:
            static bool ExistsInSecond(const int element,
                                       const std::vector<int>& falseResults)
            {
                // Check if the element exists in the second vector
                return std::find(falseResults.begin(), falseResults.end(),
                                 element) != falseResults.end();
            }

            static void RemoveElementsInSecond(
                std::vector<int>& indexes, const std::vector<int>& secondVector)
            {
                // Use std::remove_if with a custom predicate
                auto newEnd = std::remove_if(indexes.begin(), indexes.end(),
                                             [&](const int& element)
                                             {
                                                 return ExistsInSecond(
                                                     element, secondVector);
                                             });

                // Erase the elements from the vector
                indexes.erase(newEnd, indexes.end());
            }

           public:
            auto ToString() const -> const std::string override
            {
                return fmt::format("Not ({})", m_condition->ToString());
            }

           protected:
            UCondition m_condition;
        };

        //////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////

        class ComparisonCondition : public Condition
        {
           public:
            using Query::ICondition::Check;

           public:
            ComparisonCondition(const std::string columnName,
                                const UDynamicValue& value) :
                m_columnName{columnName},
                m_value{Interface::CopyUDynValue(value)}
            {
                Utility::Assert(columnName.size(),
                                "Condition::ComparisonCondition, columnName "
                                "must not be empty");
            }

           public:
            void Check(const Interface::IColumn& column,
                       Interface::RowIndexes& indexes) const
            {
                for (auto&& rowIndex : indexes)
                {
                    auto&& value = column.GetElement(rowIndex);
                    if (Check(value) == false)
                    {
                        rowIndex = -1;
                    }
                }

                auto&& itr = std::remove(indexes.begin(), indexes.end(), -1);
                indexes.erase(itr, indexes.end());
            }
            void Apply(const Interface::ITable& table,
                       Interface::RowIndexes& indexes) const override final
            {
                auto&& column = table.GetColumn(m_columnName);
                Check(column, indexes);
            }

           protected:
            std::string m_columnName;
            Interface::UDynamicValue m_value;
        };

        //////////////////////////////////////////////////////////////////////

        class Equal : public ComparisonCondition
        {
           public:
            Equal(const std::string columnName, const UDynamicValue& value) :
                ComparisonCondition{columnName, std::move(value)}
            {
            }

           public:
            static auto Create(const std::string& columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<Equal>(columnName, std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return Create(m_columnName, m_value);
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                return (Interface::AreValuesEqual(m_value, value));
            }
            auto ToString() const -> const std::string override
            {
                return fmt::format(
                    "Equal ({})", Interface::ConvertUDynValueToString(m_value));
            }
        };

        //////////////////////////////////////////////////////////////////////

        class GreaterThan : public ComparisonCondition
        {
           public:
            GreaterThan(const std::string columnName,
                        const UDynamicValue& value) :
                ComparisonCondition{columnName, std::move(value)}
            {
                Utility::Assert(
                    m_value != nullptr,
                    "Condition::GreaterThan(value), value must not be nullptr");
            }

           public:
            static auto Create(const std::string& columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<GreaterThan>(columnName,
                                                     std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return Create(m_columnName, m_value);
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                if (value == nullptr)
                {
                    return false;
                }

                return (*value > *m_value);
            }
            auto ToString() const -> const std::string override
            {
                return fmt::format(
                    "GreaterThan ({})",
                    Interface::ConvertUDynValueToString(m_value));
            }
        };

        //////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////

        class ReusingComparison : public Condition
        {
           public:
            ReusingComparison(UCondition condition) :
                m_condition{std::move(condition)}
            {
                Utility::Assert(m_condition != nullptr,
                                "Condition::ReusingComparison(condition), "
                                "condition must not be nullptr");
            }

           public:
            auto Check(const Interface::UDynamicValue& value) const
                -> bool override
            {
                return m_condition->Check(value);
            }
            void Apply(const Interface::ITable& table,
                       Interface::RowIndexes& indexes) const override final
            {
                indexes = m_condition->Apply(table);
            }

           protected:
            UCondition m_condition;
        };

        //////////////////////////////////////////////////////////////////////

        class NotEqual : public ReusingComparison
        {
           public:
            using ReusingComparison::ReusingComparison;

           public:
            NotEqual(const std::string columnName, const UDynamicValue& value) :
                ReusingComparison{
                    Not::Create(Equal::Create(columnName, std::move(value)))}
            {
            }

           public:
            static auto Create(const std::string columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<NotEqual>(columnName, std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return std::make_unique<NotEqual>(m_condition->Copy());
            }

            auto ToString() const -> const std::string override
            {
                return fmt::format("NotEqual ({})", m_condition->ToString());
            }
        };

        //////////////////////////////////////////////////////////////////////

        class GreaterThanOrEqualTo : public ReusingComparison
        {
           public:
            using ReusingComparison::ReusingComparison;

           public:
            GreaterThanOrEqualTo(const std::string columnName,
                                 const UDynamicValue& value) :
                ReusingComparison{
                    Or::Create(GreaterThan::Create(columnName, value),
                               Equal::Create(columnName, value))}
            {
            }

           public:
            static auto Create(const std::string columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<GreaterThanOrEqualTo>(columnName,
                                                              std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return std::make_unique<GreaterThanOrEqualTo>(
                    m_condition->Copy());
            }

            auto ToString() const -> const std::string override
            {
                return fmt::format("GreaterThanOrEqualTo ({})",
                                   m_condition->ToString());
            }
        };

        //////////////////////////////////////////////////////////////////////

        class LessThan : public ReusingComparison
        {
           public:
            using ReusingComparison::ReusingComparison;

           public:
            LessThan(const std::string columnName, const UDynamicValue& value) :
                ReusingComparison{Not::Create(
                    GreaterThanOrEqualTo::Create(columnName, std::move(value)))}
            {
            }

           public:
            static auto Create(const std::string columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<LessThan>(columnName, std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return std::make_unique<LessThan>(m_condition->Copy());
            }

            auto ToString() const -> const std::string override
            {
                return fmt::format("LessThan ({})", m_condition->ToString());
            }
        };

        //////////////////////////////////////////////////////////////////////

        class LessThanOrEqualTo : public ReusingComparison
        {
           public:
            using ReusingComparison::ReusingComparison;

           public:
            LessThanOrEqualTo(const std::string columnName,
                              const UDynamicValue& value) :
                ReusingComparison{Not::Create(
                    GreaterThan::Create(columnName, std::move(value)))}
            {
            }

           public:
            static auto Create(const std::string columnName,
                               const UDynamicValue& value) -> UCondition
            {
                return std::make_unique<LessThanOrEqualTo>(columnName,
                                                           std::move(value));
            }

           public:
            auto Copy() const -> UCondition override
            {
                return std::make_unique<LessThanOrEqualTo>(m_condition->Copy());
            }

            auto ToString() const -> const std::string override
            {
                return fmt::format("LessThanOrEqualTo ({})",
                                   m_condition->ToString());
            }
        };

        //////////////////////////////////////////////////////////////////////
        //                                                                  //
        //////////////////////////////////////////////////////////////////////

    }  // namespace

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Query::CreateConditionAnd(UCondition left, UCondition right)
        -> UCondition
    {
        return And::Create(std::move(left), std::move(right));
    }
    auto Query::CreateConditionOr(UCondition left, UCondition right)
        -> UCondition
    {
        return Or::Create(std::move(left), std::move(right));
    }
    auto Query::CreateConditionNot(UCondition condition) -> UCondition
    {
        return Not::Create(std::move(condition));
    }

    //////////////////////////////////////////////////////////////////////

    auto Query::CreateConditionEqual(const std::string columnName,
                                             const UDynamicValue& value)
        -> UCondition
    {
        return Equal::Create(columnName, value);
    }
    auto Query::CreateConditionNotEqual(const std::string columnName,
                                                const UDynamicValue& value)
        -> UCondition
    {
        return NotEqual::Create(columnName, value);
    }

    auto Query::CreateConditionGreaterThan(const std::string columnName,
                                                   const UDynamicValue& value)
        -> UCondition
    {
        return GreaterThan::Create(columnName, value);
    }
    auto Query::CreateConditionLessThan(const std::string columnName,
                                                const UDynamicValue& value)
        -> UCondition
    {
        return LessThan::Create(columnName, value);
    }

    auto Query::CreateConditionGreaterThanOrEqualTo(
        const std::string columnName, const UDynamicValue& value) -> UCondition
    {
        return GreaterThanOrEqualTo::Create(columnName, value);
    }
    auto Query::CreateConditionLessThanOrEqualTo(
        const std::string columnName, const UDynamicValue& value) -> UCondition
    {
        return LessThanOrEqualTo::Create(columnName, value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // auto Query::ApplyCondition(const Interface::ITable& table,
    //                                    const ICondition& condition)
    //     -> Interface::UTable
    // {
    //     Interface::RowIndexes indexes =
    //     Interface::CreateRowIndexes(table.RowsCount());

    //     condition.Apply(table, indexes);
    //     // fmt::println("Query::ApplyCondition: indexes = {}",
    //     // indexes);
    //     return table.CopyUsingRowIndexes(indexes);
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
