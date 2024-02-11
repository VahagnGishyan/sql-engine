
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

class OperationInsertInto : public ::testing::Test
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

    Interface::UTable utable;
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationInsertInto, SingleRow)
{
    auto GetSingleRow = []()
    {
        Query::InsertIntoData values{};
        values["Age"].push_back(Interface::CreateUDynValue(40));
        values["Salary"].push_back(Interface::CreateUDynValue(80000.0));
        values["Name"].push_back(Interface::CreateUDynValue("Frank"));
        return values;
    };

    auto insertOp    = CreateOpInsertInto(GetSingleRow());
    auto resultTable = insertOp->Execute(*utable);

    auto shouldBeTable = utable->Copy();
    auto values        = GetSingleRow();
    for (auto&& value : values)
    {
        auto&& column = shouldBeTable->GetColumn(value.first);
        for (auto&& value : value.second)
        {
            column.AddElement(Interface::CopyUDynValue(value));
        }
    }

    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationInsertInto, MultipleRows)
{
    auto GetSingleRow = []()
    {
        Query::InsertIntoData values{};

        // Adding multiple values for each column
        values["Age"].push_back(Interface::CreateUDynValue(40));
        values["Age"].push_back(Interface::CreateUDynValue(35));
        values["Age"].push_back(Interface::CreateUDynValue(28));

        values["Salary"].push_back(Interface::CreateUDynValue(80000.0));
        values["Salary"].push_back(Interface::CreateUDynValue(75000.0));
        values["Salary"].push_back(Interface::CreateUDynValue(90000.0));

        values["Name"].push_back(Interface::CreateUDynValue("Frank"));
        values["Name"].push_back(Interface::CreateUDynValue("Alice"));
        values["Name"].push_back(Interface::CreateUDynValue("Bob"));

        // Add more data as needed
        return values;
    };

    auto insertOp    = CreateOpInsertInto(GetSingleRow());
    auto resultTable = insertOp->Execute(*utable);

    auto shouldBeTable = utable->Copy();
    auto values        = GetSingleRow();
    for (auto&& value : values)
    {
        auto&& column = shouldBeTable->GetColumn(value.first);
        for (auto&& value : value.second)
        {
            column.AddElement(Interface::CopyUDynValue(value));
        }
    }

    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationInsertInto, EmptyRows)
{
    auto GetSingleRow = []()
    {
        Query::InsertIntoData values{};
        return values;
    };

    ASSERT_THROW(CreateOpInsertInto(GetSingleRow()), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST_F(OperationInsertInto, InvalidCases)
{
    {
        auto GetSingleRow = []()
        {
            Query::InsertIntoData values{};
            values["UnknownCase"].push_back(Interface::CreateUDynValue(40));
            values["Salary"].push_back(Interface::CreateUDynValue(80000.0));
            values["Name"].push_back(Interface::CreateUDynValue("Frank"));
            return values;
        };

        auto insertOp = CreateOpInsertInto(GetSingleRow());
        ASSERT_THROW(insertOp->Execute(*utable), std::exception);
    }

    {
        auto GetSingleRow = []()
        {
            Query::InsertIntoData values{};
            values["Salary"].push_back(Interface::CreateUDynValue(80000.0));
            values["Name"].push_back(Interface::CreateUDynValue("Frank"));
            return values;
        };

        auto insertOp = CreateOpInsertInto(GetSingleRow());
        ASSERT_THROW(insertOp->Execute(*utable), std::exception);
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
