
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "database/database.hpp"
#include "sql-operations/condition.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;
using namespace SQLEngine::QueryExecutor;
using namespace SQLEngine::Interface;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

class ConditionTable : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        // Create a test table with columns
        utable = DataBase::CreateTable("test-table-name");

        std::map<std::string, Interface::UDynamicValue> columnData;

        auto&& columnAge =
            DataBase::CreateColumn("Age", Interface::DynamicType::Int);
        auto&& columnSalary =
            DataBase::CreateColumn("Salary", Interface::DynamicType::Double);
        auto&& columnName =
            DataBase::CreateColumn("Name", Interface::DynamicType::String);

        columnAge->AddElement(Interface::CreateUDynValue(25));
        columnAge->AddElement(Interface::CreateUDynValue(30));
        columnAge->AddElement(Interface::CreateUDynValue(30));
        columnAge->AddElement(Interface::CreateUDynValue(35));
        columnAge->AddElement(Interface::CreateUDynValue(30));

        columnSalary->AddElement(Interface::CreateUDynValue(50000.0));
        columnSalary->AddElement(Interface::CreateUDynValue(60000.0));
        columnSalary->AddElement(Interface::CreateUDynValue(60000.0));
        columnSalary->AddElement(Interface::CreateUDynValue(75000.0));
        columnSalary->AddElement(Interface::CreateUDynValue(60000.0));

        columnName->AddElement(Interface::CreateUDynValue("Alice"));
        columnName->AddElement(Interface::CreateUDynValue("Bob"));
        columnName->AddElement(Interface::CreateUDynValue("Charlie"));
        columnName->AddElement(Interface::CreateUDynValue("David"));
        columnName->AddElement(Interface::CreateUDynValue("Eva"));

        utable->AddColumn(std::move(columnAge));
        utable->AddColumn(std::move(columnSalary));
        utable->AddColumn(std::move(columnName));
    }

    // void CheckResult(const Interface::ITable& newTable,
    //                  const std::vector<int>& indexes)
    // {
    //     if (utable->GetName() != newTable.GetName())
    //     {
    //         throw std::runtime_error{fmt::format(
    //             "ConditionTable::CheckResult, ori-table-name: {} and "
    //             "new-table-name: {} must be equal",
    //             utable->GetName(), newTable.GetName())};
    //     }
    //     if (utable->ColumnsCount() != newTable.ColumnsCount())
    //     {
    //         throw std::runtime_error{fmt::format(
    //             "ConditionTable::CheckResult, ori-table-size: {} and "
    //             "new-table-size: {} must be equal",
    //             utable->ColumnsCount(), newTable.ColumnsCount())};
    //     }

    //     auto columnSize = newTable.ColumnsCount();

    //     for (int columnIndex = 0; columnIndex < columnSize; ++columnIndex)
    //     {
    //         auto&& oriColumn = utable->GetColumn(columnIndex);
    //         auto&& newColumn = newTable.GetColumn(columnIndex);

    //         if (oriColumn.GetName() != newColumn.GetName())
    //         {
    //             throw std::runtime_error{fmt::format(
    //                 "ConditionTable::CheckResult, ori-column-name: {} and "
    //                 "new-column-name: {} must be equal",
    //                 oriColumn.GetName(), newColumn.GetName())};
    //         }
    //         if (oriColumn.GetType() != newColumn.GetType())
    //         {
    //             throw std::runtime_error{fmt::format(
    //                 "ConditionTable::CheckResult, ori-column-type: {} and "
    //                 "new-column-type: {} must be equal",
    //                 Interface::GetDynamicTypeNameAsString(oriColumn.GetType()),
    //                 Interface::GetDynamicTypeNameAsString(
    //                     newColumn.GetType()))};
    //         }
    //         if (oriColumn.GetSize() < newColumn.GetSize())
    //         {
    //             throw std::runtime_error{
    //                 fmt::format("ConditionTable::CheckResult,
    //                 ori-column-size: "
    //                             "{} must be greather then or equal to "
    //                             "new-column-size: {}",
    //                             oriColumn.GetSize(), newColumn.GetSize())};
    //         }

    //         int newIndex = -1;
    //         for (auto oriIndex : indexes)
    //         {
    //             ++newIndex;
    //             auto&& oriValue = oriColumn.GetElement(oriIndex);
    //             auto&& newValue = newColumn.GetElement(newIndex);

    //             if (Interface::AreValuesEqual(oriValue, newValue) == false)
    //             {
    //                 throw std::runtime_error{fmt::format(
    //                     "ConditionTable::CheckResult, ori-value: {} and "
    //                     "new-value: {} must be equal",
    //                     Interface::ConvertUDynValueToString(oriValue),
    //                     Interface::ConvertUDynValueToString(newValue))};
    //             }
    //         }
    //     }
    // }

    void CheckResult(const std::vector<int>& actual,
                     const std::vector<int>& shouldBe)
    {
        if (actual.size() != shouldBe.size())
        {
            throw std::runtime_error{fmt::format(
                "ConditionTable::CheckResult(vec, vec), actual-size: "
                "{} must be equal to "
                "should-be-size: {}",
                actual.size(), shouldBe.size())};
        }
        const int size = actual.size();
        for (int index = 0; index < size; ++index)
        {
            if (actual[index] != shouldBe[index])
            {
                throw std::runtime_error{
                    fmt::format("ConditionTable::CheckResult(vec, vec), "
                                "actual-value: {} and "
                                "should-be-value: {} must be equal",
                                actual[index], shouldBe[index])};
            }
        }
    }

    // Add your class members and necessary includes

    Interface::UTable utable;
};

TEST_F(ConditionTable, EqualCondition)
{
    auto condition =
        CreateConditionEqual("Age", Interface::CreateUDynValue(30));
    const std::vector<int> shouldBe{1, 2, 4};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

TEST_F(ConditionTable, NotEqualCondition)
{
    auto condition =
        CreateConditionNotEqual("Age", Interface::CreateUDynValue(30));
    const std::vector<int> shouldBe{0, 3};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

TEST_F(ConditionTable, GreaterThanCondition)
{
    auto condition =
        CreateConditionGreaterThan("Age", Interface::CreateUDynValue(30));
    const std::vector<int> shouldBe{3};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

TEST_F(ConditionTable, GreaterThanOrEqualToCondition)
{
    auto condition = CreateConditionGreaterThanOrEqualTo(
        "Age", Interface::CreateUDynValue(30));
    const std::vector<int> shouldBe{1, 2, 3, 4};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

TEST_F(ConditionTable, LessThanCondition)
{
    auto condition =
        CreateConditionLessThan("Age", Interface::CreateUDynValue(35));
    const std::vector<int> shouldBe{0, 1, 2, 4};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

TEST_F(ConditionTable, LessThanOrEqualToCondition)
{
    auto condition =
        CreateConditionLessThanOrEqualTo("Age", Interface::CreateUDynValue(35));
    const std::vector<int> shouldBe{0, 1, 2, 3, 4};
    auto&& actual = condition->Apply(*utable);
    ASSERT_NO_THROW(CheckResult(actual, shouldBe));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
