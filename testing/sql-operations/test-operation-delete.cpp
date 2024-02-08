
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "database/database.hpp"
#include "sql-operations/operations.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;
using namespace SQLEngine::SQLOperations;
using namespace SQLEngine::Interface;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

class OperationDelete : public ::testing::Test
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

        auto&& columnAgeData = GetAgeColumnData();
        for (auto&& age : columnAgeData)
        {
            columnAge->AddElement(Interface::CreateUDynValue(age));
        }

        auto&& columnSalaryData = GetSalaryColumnData();
        for (auto&& salary : columnSalaryData)
        {
            columnSalary->AddElement(Interface::CreateUDynValue(salary));
        }

        auto&& columnNameData = GetNameColumnData();
        for (auto&& name : columnNameData)
        {
            columnName->AddElement(Interface::CreateUDynValue(name));
        }

        utable->AddColumn(std::move(columnAge));
        utable->AddColumn(std::move(columnSalary));
        utable->AddColumn(std::move(columnName));
    }

    //////////////////////////////////////////////////////////////////////

   protected:
    auto GetAgeColumnData() const -> const std::vector<int>&
    {
        static std::vector<int> data{
            25, 30, 30, 35, 30,
        };
        return data;
    }

    auto GetSalaryColumnData() const -> const std::vector<double>&
    {
        static std::vector<double> data{
            50000.0, 60000.0, 60000.0, 75000.0, 60000.0,
        };
        return data;
    }

    auto GetNameColumnData() const -> const std::vector<std::string>&
    {
        static std::vector<std::string> data{
            "Alice", "Bob", "Charlie", "David", "Eva",
        };
        return data;
    }

    //////////////////////////////////////////////////////////////////////

   protected:
    auto CreateShouldBeTable(const UCondition& condition) -> UTable
    {
        auto reverse = CreateConditionNot(condition->Copy());
        auto selectOp =
            CreateOpSelect(*utable->ListColumns(), std::move(reverse));
        return selectOp->Execute(*utable);
    }

    //////////////////////////////////////////////////////////////////////

   protected:
    void CheckTables(const Interface::ITable& actual,
                     const Interface::ITable& shouldBe)
    {
        if (actual.GetName() != shouldBe.GetName())
        {
            throw std::runtime_error{fmt::format(
                "ConditionTable::CheckResult, actual-table-name: {} and "
                "should-be-table-name: {} must be equal",
                actual.GetName(), shouldBe.GetName())};
        }
        if (actual.ColumnsCount() != shouldBe.ColumnsCount())
        {
            throw std::runtime_error{fmt::format(
                "ConditionTable::CheckResult, actual-table-size: {} and "
                "should-be-table-size: {} must be equal",
                actual.ColumnsCount(), shouldBe.ColumnsCount())};
        }

        auto columnSize = actual.ColumnsCount();
        for (int columnIndex = 0; columnIndex < columnSize; ++columnIndex)
        {
            auto&& actualColumn   = actual.GetColumn(columnIndex);
            auto&& shouldbeColumn = shouldBe.GetColumn(columnIndex);

            if (actualColumn.GetName() != shouldbeColumn.GetName())
            {
                throw std::runtime_error{fmt::format(
                    "ConditionTable::CheckResult, actual-column-name: {} and "
                    "should-be-column-name: {} must be equal",
                    actualColumn.GetName(), shouldbeColumn.GetName())};
            }
            if (actualColumn.GetType() != shouldbeColumn.GetType())
            {
                throw std::runtime_error{fmt::format(
                    "ConditionTable::CheckResult, actual-column-type: {} and "
                    "should-be-column-type: {} must be equal",
                    Interface::GetDynamicTypeNameAsString(
                        actualColumn.GetType()),
                    Interface::GetDynamicTypeNameAsString(
                        shouldbeColumn.GetType()))};
            }
            if (actualColumn.GetSize() != shouldbeColumn.GetSize())
            {
                throw std::runtime_error{fmt::format(
                    "ConditionTable::CheckResult, actual-column-size: "
                    "{} must be equal to "
                    "should-be-column-size: {}",
                    actualColumn.GetSize(), shouldbeColumn.GetSize())};
            }

            auto rowSize = actual.RowsCount();
            for (int rowIndex = 0; rowIndex < rowSize; ++rowIndex)
            {
                auto&& actualValue   = actualColumn.GetElement(rowIndex);
                auto&& shouldbeValue = shouldbeColumn.GetElement(rowIndex);

                if (Interface::AreValuesEqual(actualValue, shouldbeValue) ==
                    false)
                {
                    throw std::runtime_error{fmt::format(
                        "ConditionTable::CheckResult, actual-value: {} and "
                        "should-be-value: {} must be equal",
                        Interface::ConvertUDynValueToString(actualValue),
                        Interface::ConvertUDynValueToString(shouldbeValue))};
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////////
   protected:
    Interface::UTable utable;
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, AgeGreaterThan30)
{
    //////////////////////////////////////////////////////////////////////
    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition  = CreateConditionGreaterThan("Age", CreateUDynValue(30));

    auto deleteOp    = CreateOpDelete(condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto shouldBeTable = CreateShouldBeTable(condition->Copy());
    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, AgeLessThanOrEqualTo30)
{
    //////////////////////////////////////////////////////////////////////
    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition =
        CreateConditionLessThanOrEqualTo("Age", CreateUDynValue(30));

    auto deleteOp    = CreateOpDelete(condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto shouldBeTable = CreateShouldBeTable(condition->Copy());
    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, OnlySalaryAndName)
{
    //////////////////////////////////////////////////////////////////////
    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition  = CreateConditionGreaterThan("Age", CreateUDynValue(30));

    auto deleteOp    = CreateOpDelete(condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto shouldBeTable = CreateShouldBeTable(condition->Copy());
    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, UserDavid)
{
    //////////////////////////////////////////////////////////////////////
    auto equalvalue = "David";
    auto condition  = CreateConditionEqual("Name", CreateUDynValue(equalvalue));

    auto deleteOp    = CreateOpDelete(condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto shouldBeTable = CreateShouldBeTable(condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, NotUserDavid)
{
    //////////////////////////////////////////////////////////////////////
    auto equalvalue = "David";
    auto condition =
        CreateConditionNotEqual("Name", CreateUDynValue(equalvalue));

    auto deleteOp = CreateOpDelete(condition->Copy());
    ASSERT_NE(deleteOp, nullptr);
    ASSERT_NE(utable, nullptr);
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto shouldBeTable = CreateShouldBeTable(condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationDelete, NullCondition)
{
    //////////////////////////////////////////////////////////////////////
    auto condition = nullptr;
    ASSERT_THROW(CreateOpDelete(condition), std::exception);
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
