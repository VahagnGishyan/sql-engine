
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "condition.hpp"

#include <fmt/core.h>

#include <numeric>

#include "database/database.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryExecutor
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    static void SelectIndexes(const Interface::IRowOrientedTable& rotable,
                              const ICondition& condition,
                              Interface::ROTRowIndexes& indexes)
    {
        for (auto&& rowIndex : indexes)
        {
            const int columnCount = rotable.ColumnsCount();
            for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
            {
                auto&& value = rotable.GetValue(rowIndex, columnIndex);
                if (condition.Check(value) == true)
                {
                    rowIndex = -1;
                }
            }
        }

        auto&& itr = std::remove(indexes.begin(), indexes.end(), -1);
        indexes.erase(itr, indexes.end());
    }

    auto CheckCondition(const Interface::ITable& table,
                        const ICondition& condition) -> Interface::UTable
    {
        auto&& rotable = DataBase::CreateRowOrientedTable(table);

        Interface::ROTRowIndexes indexes;
        indexes.resize(rotable->ColumnsCount());
        std::iota(indexes.begin(), indexes.end(), 0);

        SelectIndexes(*rotable, condition, indexes);

        auto&& newrotable = rotable->CopyByIndexes(indexes);
        return newrotable->CreateTable();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class And : public ICondition
    {
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

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<And>(m_left->Copy(), m_right->Copy());
        }
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            return (m_left->Check(value) && m_right->Check(value));
        }
        auto ToString() const -> const std::string override
        {
            return fmt::format("({} And {})", m_left->ToString(),
                               m_right->ToString());
        }

       protected:
        UCondition m_left;
        UCondition m_right;
    };

    //////////////////////////////////////////////////////////////////////

    class Or : public ICondition
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

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<Or>(m_left->Copy(), m_right->Copy());
        }
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            return (m_left->Check(value) || m_right->Check(value));
        }
        auto ToString() const -> const std::string override
        {
            return fmt::format("({} Or {})", m_left->ToString(),
                               m_right->ToString());
        }

       protected:
        UCondition m_left;
        UCondition m_right;
    };

    //////////////////////////////////////////////////////////////////////

    class Not : public ICondition
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

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<Not>(m_condition->Copy());
        }
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            return !(m_condition->Check(value));
        }
        auto ToString() const -> const std::string override
        {
            return fmt::format("Not {}", m_condition->ToString());
        }

       protected:
        UCondition m_condition;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ComparisonCondition : public ICondition
    {
       public:
        ComparisonCondition(Interface::UDynamicValue value) :
            m_value{std::move(value)}
        {
        }

       protected:
        Interface::UDynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////

    class Equal : public ComparisonCondition
    {
       public:
        Equal(Interface::UDynamicValue value) :
            ComparisonCondition{std::move(value)}
        {
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<Equal>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<Equal>(Interface::CopyUDynValue(m_value));
        }

       public:
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            return (Interface::AreValuesEqual(m_value, value));
        }
        auto ToString() const -> const std::string override
        {
            return fmt::format("Equal {}",
                               Interface::ConvertUDynValueToString(m_value));
        }
    };

    //////////////////////////////////////////////////////////////////////

    class GreaterThan : public ComparisonCondition
    {
       public:
        GreaterThan(Interface::UDynamicValue value) :
            ComparisonCondition{std::move(value)}
        {
            Utility::Assert(
                m_value != nullptr,
                "Condition::GreaterThan(value), value must not be nullptr");
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<GreaterThan>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<GreaterThan>(
                Interface::CopyUDynValue(m_value));
        }

       public:
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            if (value == nullptr)
            {
                return false;
            }

            return (*m_value > *value);
        }
        auto ToString() const -> const std::string override
        {
            return fmt::format("GreaterThan {}",
                               Interface::ConvertUDynValueToString(m_value));
        }
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ReusingComparison : public ICondition
    {
       public:
        ReusingComparison(UCondition condition) :
            m_condition{std::move(m_condition)}
        {
            Utility::Assert(m_condition != nullptr,
                            "Condition::ReusingComparison(condition), "
                            "condition must not be nullptr");
        }

       public:
        auto Check(const Interface::UDynamicValue& value) const -> bool override
        {
            return m_condition->Check(value);
        }

       protected:
        UCondition m_condition;
    };

    //////////////////////////////////////////////////////////////////////

    class NotEqual : public ReusingComparison
    {
       public:
        using ReusingComparison::ReusingComparison;
        NotEqual(Interface::UDynamicValue value) :
            ReusingComparison{Not::Create(Equal::Create(std::move(value)))}
        {
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<NotEqual>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<NotEqual>(m_condition->Copy());
        }

        auto ToString() const -> const std::string override
        {
            return fmt::format("NotEqual {}", m_condition->ToString());
        }
    };

    //////////////////////////////////////////////////////////////////////

    class GreaterThanOrEqualTo : public ReusingComparison
    {
       public:
        using ReusingComparison::ReusingComparison;
        GreaterThanOrEqualTo(Interface::UDynamicValue value) :
            ReusingComparison{
                Or::Create(GreaterThan::Create(Interface::CopyUDynValue(value)),
                           Equal::Create(std::move(value)))}
        {
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<GreaterThanOrEqualTo>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<GreaterThanOrEqualTo>(m_condition->Copy());
        }

        auto ToString() const -> const std::string override
        {
            return fmt::format("GreaterThanOrEqualTo {}",
                               m_condition->ToString());
        }
    };

    //////////////////////////////////////////////////////////////////////

    class LessThan : public ReusingComparison
    {
       public:
        using ReusingComparison::ReusingComparison;
        LessThan(Interface::UDynamicValue value) :
            ReusingComparison{
                Not::Create(GreaterThanOrEqualTo::Create(std::move(value)))}
        {
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<LessThan>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<LessThan>(m_condition->Copy());
        }

        auto ToString() const -> const std::string override
        {
            return fmt::format("LessThan {}", m_condition->ToString());
        }
    };

    //////////////////////////////////////////////////////////////////////

    class LessThanOrEqualTo : public ReusingComparison
    {
       public:
        using ReusingComparison::ReusingComparison;
        LessThanOrEqualTo(Interface::UDynamicValue value) :
            ReusingComparison{
                Not::Create(GreaterThan::Create(std::move(value)))}
        {
        }

       public:
        static auto Create(Interface::UDynamicValue value) -> UCondition
        {
            return std::make_unique<LessThanOrEqualTo>(std::move(value));
        }

       public:
        auto Copy() const -> UCondition override
        {
            return std::make_unique<LessThanOrEqualTo>(m_condition->Copy());
        }

        auto ToString() const -> const std::string override
        {
            return fmt::format("LessThanOrEqualTo {}", m_condition->ToString());
        }
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
