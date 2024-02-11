
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "database/database.hpp"
#include "query/executors.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;
using namespace SQLEngine::Query;
using namespace SQLEngine::Interface;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

class OperationSelect : public ::testing::Test
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
    auto CreateShouldBeTable(const ColumnNameList& columnNameList,
                             const RowIndexes& indexes) -> UTable
    {
        auto shouldBeTable = DataBase::CreateTable("test-table-name");
        auto&& columnAge =
            DataBase::CreateColumn("Age", Interface::DynamicType::Int);
        auto&& columnSalary =
            DataBase::CreateColumn("Salary", Interface::DynamicType::Double);
        auto&& columnName =
            DataBase::CreateColumn("Name", Interface::DynamicType::String);

        //////////////////////////////////////////////////////////////////////
        auto&& columnAgeData    = GetAgeColumnData();
        auto&& columnSalaryData = GetSalaryColumnData();
        auto&& columnNameData   = GetNameColumnData();
        //////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////
        for (auto index : indexes)
        {
            columnAge->AddElement(
                Interface::CreateUDynValue(columnAgeData[index]));
            columnSalary->AddElement(
                Interface::CreateUDynValue(columnSalaryData[index]));
            columnName->AddElement(
                Interface::CreateUDynValue(columnNameData[index]));
        }
        //////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////
        if (std::find(columnNameList.begin(), columnNameList.end(), "Age") !=
            columnNameList.end())
        {
            shouldBeTable->AddColumn(std::move(columnAge));
        }
        if (std::find(columnNameList.begin(), columnNameList.end(), "Salary") !=
            columnNameList.end())
        {
            shouldBeTable->AddColumn(std::move(columnSalary));
        }
        if (std::find(columnNameList.begin(), columnNameList.end(), "Name") !=
            columnNameList.end())
        {
            shouldBeTable->AddColumn(std::move(columnName));
        }
        // should be table is already created
        //////////////////////////////////////////////////////////////////////

        return shouldBeTable;
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

template <typename Type>
auto GetCheckedRowIndexes(
    const std::vector<Type>& array,
    const std::function<bool(const Type& value)> condition) -> RowIndexes
{
    auto indexes = CreateRowIndexes(array.size());
    for (auto&& index : indexes)
    {
        if (condition(array[index]) == false)
        {
            index = -1;
        }
    }
    auto pos = std::remove(indexes.begin(), indexes.end(), -1);
    indexes.erase(pos, indexes.end());
    return indexes;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, AgeGreaterThan30)
{
    //////////////////////////////////////////////////////////////////////
    // Choose some columns from the table
    ColumnNameList columnNameList{"Age", "Salary", "Name"};

    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition  = CreateConditionGreaterThan("Age", CreateUDynValue(30));

    auto selectOp    = CreateOpSelect(columnNameList, std::move(condition));
    auto resultTable = selectOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto indexes = GetCheckedRowIndexes<int>(GetAgeColumnData(),
                                             [greaterThan](int value)
                                             {
                                                 return (value > greaterThan);
                                             });
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Create a test table with columns
    auto shouldBeTable = CreateShouldBeTable(columnNameList, indexes);
    //////////////////////////////////////////////////////////////////////

    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, AgeLessThanOrEqualTo30)
{
    //////////////////////////////////////////////////////////////////////
    // Choose some columns from the table
    ColumnNameList columnNameList{"Age", "Salary", "Name"};

    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition =
        CreateConditionLessThanOrEqualTo("Age", CreateUDynValue(30));

    auto selectOp    = CreateOpSelect(columnNameList, std::move(condition));
    auto resultTable = selectOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto indexes = GetCheckedRowIndexes<int>(GetAgeColumnData(),
                                             [greaterThan](int value)
                                             {
                                                 return (value <= greaterThan);
                                             });
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Create a test table with columns
    auto shouldBeTable = CreateShouldBeTable(columnNameList, indexes);
    //////////////////////////////////////////////////////////////////////

    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, OnlySalaryAndName)
{
    //////////////////////////////////////////////////////////////////////
    // Choose some columns from the table
    ColumnNameList columnNameList{"Salary", "Name"};

    // Create some conditions
    // Example: Select rows where Age is greater than 30
    int greaterThan = 30;
    auto condition  = CreateConditionGreaterThan("Age", CreateUDynValue(30));

    auto selectOp    = CreateOpSelect(columnNameList, std::move(condition));
    auto resultTable = selectOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto indexes = GetCheckedRowIndexes<int>(GetAgeColumnData(),
                                             [greaterThan](int value)
                                             {
                                                 return (value > greaterThan);
                                             });
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Create a test table with columns
    auto shouldBeTable = CreateShouldBeTable(columnNameList, indexes);
    //////////////////////////////////////////////////////////////////////

    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, UserDavid)
{
    //////////////////////////////////////////////////////////////////////
    ColumnNameList columnNameList{"Age", "Salary", "Name"};
    auto equalvalue = "David";
    auto condition  = CreateConditionEqual("Name", CreateUDynValue(equalvalue));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto selectOp    = CreateOpSelect(columnNameList, std::move(condition));
    auto resultTable = selectOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto indexes =
        GetCheckedRowIndexes<std::string>(GetNameColumnData(),
                                          [equalvalue](const std::string& value)
                                          {
                                              return (value == equalvalue);
                                          });
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Create a test table with columns
    auto shouldBeTable = CreateShouldBeTable(columnNameList, indexes);
    //////////////////////////////////////////////////////////////////////

    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, NotUserDavid)
{
    //////////////////////////////////////////////////////////////////////
    ColumnNameList columnNameList{"Age", "Salary", "Name"};
    auto equalvalue = "David";
    auto condition =
        CreateConditionNotEqual("Name", CreateUDynValue(equalvalue));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto selectOp    = CreateOpSelect(columnNameList, std::move(condition));
    auto resultTable = selectOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // create table should be
    auto indexes =
        GetCheckedRowIndexes<std::string>(GetNameColumnData(),
                                          [equalvalue](const std::string& value)
                                          {
                                              return (value != equalvalue);
                                          });
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Create a test table with columns
    auto shouldBeTable = CreateShouldBeTable(columnNameList, indexes);
    //////////////////////////////////////////////////////////////////////

    // Check tables equality
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationSelect, EmptyColumnNames)
{
    //////////////////////////////////////////////////////////////////////
    ColumnNameList columnNameList{};
    auto equalvalue = "David";
    auto condition =
        CreateConditionNotEqual("Name", CreateUDynValue(equalvalue));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    ASSERT_THROW(CreateOpSelect(columnNameList, std::move(condition)),
                 std::exception);
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
