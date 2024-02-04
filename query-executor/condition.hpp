
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-table.hpp"
#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryExecutor
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ICondition;

    using UCondition = std::unique_ptr<ICondition>;

    class PROJECT_SHARED_EXPORT ICondition
    {
       public:
        virtual ~ICondition() = default;

       public:
        virtual auto Copy() const -> UCondition = 0;

       public:
        virtual auto Check(const Interface::UDynamicValue& value) const
            -> bool                                              = 0;
        virtual void Check(const Interface::ITable&,
                           Interface::RowIndexes& indexes) const = 0;

       public:
        // for debug
        virtual auto ToString() const -> const std::string = 0;
    };

    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT CreateConditionAnd(UCondition left,
                                                  UCondition right)
        -> UCondition;
    auto PROJECT_SHARED_EXPORT CreateConditionOr(UCondition left,
                                                 UCondition right)
        -> UCondition;
    auto PROJECT_SHARED_EXPORT CreateConditionNot(UCondition condition)
        -> UCondition;

    auto PROJECT_SHARED_EXPORT CreateConditionEqual(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;
    auto PROJECT_SHARED_EXPORT CreateConditionNotEqual(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;

    auto PROJECT_SHARED_EXPORT CreateConditionGreaterThan(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;
    auto PROJECT_SHARED_EXPORT CreateConditionLessThan(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;

    auto PROJECT_SHARED_EXPORT CreateConditionGreaterThanOrEqualTo(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;
    auto PROJECT_SHARED_EXPORT CreateConditionLessThanOrEqualTo(
        const std::string columnName, const Interface::UDynamicValue& value)
        -> UCondition;

    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT AcceptCondition(const Interface::ITable&,
                                               const ICondition&)
        -> Interface::UTable;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
