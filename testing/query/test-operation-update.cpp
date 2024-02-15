
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>
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

class OperationUpdate : public ::testing::Test
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
    auto CreateShouldBeTable(const UpdateData& data,
                             const UCondition& condition) -> UTable
    {
        auto shouldBeTable = utable->Copy();
        //////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////
        auto UpdateColumn = [this](IColumn& column, const RowIndexes& indexes,
                                   auto&& updatedValue)
        {
            for (int index : indexes)
            {
                column.SetElement(index, CopyUDynValue(updatedValue));
            }
        };
        //////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////
        auto indexes = condition->Apply(*shouldBeTable);
        if (data.find("Age") != data.end())
        {
            auto&& column       = shouldBeTable->GetColumn("Age");
            auto&& updatedValue = data.find("Age")->second;
            UpdateColumn(column, indexes, updatedValue);
        }
        if (data.find("Salary") != data.end())
        {
            auto&& column       = shouldBeTable->GetColumn("Salary");
            auto&& updatedValue = data.find("Salary")->second;
            UpdateColumn(column, indexes, updatedValue);
        }
        if (data.find("Name") != data.end())
        {
            auto&& column       = shouldBeTable->GetColumn("Name");
            auto&& updatedValue = data.find("Name")->second;
            UpdateColumn(column, indexes, updatedValue);
        }
        //////////////////////////////////////////////////////////////////////

        return shouldBeTable;
    }

    //////////////////////////////////////////////////////////////////////Eva

    void PrintColumn(const IColumn& column)
    {
        fmt::println("column: {}", column.GetName());
        fmt::println("column-type: {}",
                     GetDynamicTypeNameAsString(column.GetType()));
        fmt::println("column-size: {}", column.GetSize());

        const int size = column.GetSize();
        std::vector<std::string> elements{};
        elements.reserve(size);
        for (int index = 0; index < size; ++index)
        {
            elements.push_back(
                ConvertUDynValueToString(column.GetElement(index)));
        }
        fmt::println("column-elements: {}", elements);
    }

    //////////////////////////////////////////////////////////////////////Eva

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

TEST_F(OperationUpdate, AgeGreaterThan30)
{
    //////////////////////////////////////////////////////////////////////
    auto AddUpdateDataValues = []()
    {
        UpdateData data;
        data["Age"]    = CreateUDynValue(40);
        data["Salary"] = CreateUDynValue(80000.0);
        return data;
    };

    UpdateData data = AddUpdateDataValues();

    int greaterThan = 30;
    auto condition  = CreateConditionGreaterThan("Age", CreateUDynValue(30));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto deleteOp    = CreateOpUpdate(std::move(data), condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    data               = AddUpdateDataValues();
    auto shouldBeTable = CreateShouldBeTable(data, condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationUpdate, AgeEqualEva)
{
    //////////////////////////////////////////////////////////////////////
    auto AddUpdateDataValues = []()
    {
        UpdateData data;
        data["Age"]    = CreateUDynValue(40);
        data["Salary"] = CreateUDynValue(80000.0);
        data["Name"]   = CreateUDynValue("Any");
        return data;
    };

    UpdateData data = AddUpdateDataValues();

    int greaterThan = 30;
    auto condition  = CreateConditionEqual("Name", CreateUDynValue("Eva"));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto deleteOp    = CreateOpUpdate(std::move(data), condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    data               = AddUpdateDataValues();
    auto shouldBeTable = CreateShouldBeTable(data, condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationUpdate, OnlyAgeAndSalary)
{
    //////////////////////////////////////////////////////////////////////
    auto AddUpdateDataValues = []()
    {
        UpdateData data;
        data["Age"]    = CreateUDynValue(40);
        data["Salary"] = CreateUDynValue(80000.0);
        return data;
    };

    UpdateData data = AddUpdateDataValues();

    int greaterThan = 30;
    auto condition  = CreateConditionEqual("Name", CreateUDynValue("Eva"));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto deleteOp    = CreateOpUpdate(std::move(data), condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    data               = AddUpdateDataValues();
    auto shouldBeTable = CreateShouldBeTable(data, condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST_F(OperationUpdate, NotUserEva)
{
    //////////////////////////////////////////////////////////////////////
    auto AddUpdateDataValues = []()
    {
        UpdateData data;
        data["Age"]    = CreateUDynValue(-40);
        data["Salary"] = CreateUDynValue(80000.0);
        return data;
    };

    UpdateData data = AddUpdateDataValues();

    int greaterThan = 30;
    auto condition  = CreateConditionNotEqual("Name", CreateUDynValue("Eva"));
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto deleteOp    = CreateOpUpdate(std::move(data), condition->Copy());
    auto resultTable = deleteOp->Execute(*utable);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    data               = AddUpdateDataValues();
    auto shouldBeTable = CreateShouldBeTable(data, condition->Copy());
    ASSERT_NO_THROW(CheckTables(*resultTable, *shouldBeTable));
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
