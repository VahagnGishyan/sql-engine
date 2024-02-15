
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "debug-db.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace
    {
        auto ColumnToStrList(const Interface::IColumn& column)
            -> std::vector<std::string>
        {
            std::vector<std::string> list;
            list.push_back("column: " + column.GetName());
            list.push_back(
                "column-type: " +
                Interface::GetDynamicTypeNameAsString(column.GetType()));
            list.push_back("column-size: " + column.GetSize());

            const int size = column.GetSize();
            std::vector<std::string> elements;
            for (int index = 0; index < size; ++index)
            {
                elements.push_back(Interface::ConvertUDynValueToString(
                    column.GetElement(index)));
            }
            list.push_back(fmt::format("\telements: {}", elements));
            return list;
        }

        auto TableToStrList(const Interface::ITable& table)
            -> std::vector<std::string>
        {
            std::vector<std::string> list;
            list.push_back("table: " + table.GetName());
            list.push_back("table-size: " + table.ColumnsCount());

            const int size = table.ColumnsCount();
            for (int index = 0; index < size; ++index)
            {
                auto&& column  = table.GetColumn(index);
                auto columnStr = ColumnToStrList(column);

                for (auto&& str : columnStr)
                {
                    list.push_back('\t' + str);
                }
            }
            return list;
        }

        auto DataBaseToStrList(const Interface::IDataBase& database)
            -> std::vector<std::string>
        {
            std::vector<std::string> list;
            list.push_back("database: " + database.GetName());
            list.push_back("database-size: " + database.TablesCount());

            auto&& tables = database.ListTables();
            for (auto&& tableName : *tables)
            {
                auto&& table  = database.GetTable(tableName);
                auto tableStr = TableToStrList(table);

                for (auto&& str : tableStr)
                {
                    list.push_back('\t' + str);
                }
            }

            return list;
        }
    }  // namespace

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DebugDB::CheckColumn(const Interface::IColumn& actualColumn,
                              const Interface::IColumn& shouldbeColumn)
    {
        if (actualColumn.GetName() != shouldbeColumn.GetName())
        {
            throw std::runtime_error{
                fmt::format("DebugDB::CheckResult, actual-column-name: {} and "
                            "should-be-column-name: {} must be equal",
                            actualColumn.GetName(), shouldbeColumn.GetName())};
        }
        if (actualColumn.GetType() != shouldbeColumn.GetType())
        {
            fmt::println("DebugDB::CheckColumn(), actual-column");
            PrintColumn(actualColumn);
            fmt::println("DebugDB::CheckColumn(), should-be-column");
            PrintColumn(shouldbeColumn);

            throw std::runtime_error{fmt::format(
                "DebugDB::CheckResult, actual-column-type: {} and "
                "should-be-column-type: {} must be equal",
                Interface::GetDynamicTypeNameAsString(actualColumn.GetType()),
                Interface::GetDynamicTypeNameAsString(
                    shouldbeColumn.GetType()))};
        }
        if (actualColumn.GetSize() != shouldbeColumn.GetSize())
        {
            fmt::println("DebugDB::CheckColumn(), actual-column");
            PrintColumn(actualColumn);
            fmt::println("DebugDB::CheckColumn(), should-be-column");
            PrintColumn(shouldbeColumn);

            throw std::runtime_error{
                fmt::format("DebugDB::CheckResult, actual-column-size: "
                            "{} must be equal to "
                            "should-be-column-size: {}",
                            actualColumn.GetSize(), shouldbeColumn.GetSize())};
        }

        auto rowSize = actualColumn.GetSize();
        for (int rowIndex = 0; rowIndex < rowSize; ++rowIndex)
        {
            auto&& actualValue   = actualColumn.GetElement(rowIndex);
            auto&& shouldbeValue = shouldbeColumn.GetElement(rowIndex);

            auto actualValueType   = Interface::GetRealType(actualValue);
            auto shouldbeValueType = Interface::GetRealType(shouldbeValue);

            Utility::Assert(actualValueType == actualColumn.GetType(),
                            "DebugDB::CheckColumn, actualValueType != "
                            "actualColumn.GetType()");
            Utility::Assert(shouldbeValueType == shouldbeColumn.GetType(),
                            "DebugDB::CheckColumn, shouldbeValueType != "
                            "shouldbeColumn.GetType()");
            Utility::Assert(actualValueType == shouldbeValueType,
                            "DebugDB::CheckColumn, actualValueType != "
                            "shouldbeValueType");

            if (Interface::AreValuesEqual(actualValue, shouldbeValue) == false)
            {
                fmt::println("DebugDB::CheckColumn(), actual-column");
                PrintColumn(actualColumn);
                fmt::println("DebugDB::CheckColumn(), should-be-column");
                PrintColumn(shouldbeColumn);

                throw std::runtime_error{fmt::format(
                    "DebugDB::CheckResult, actual-value: {} and "
                    "should-be-value: {} must be equal",
                    Interface::ConvertUDynValueToString(actualValue),
                    Interface::ConvertUDynValueToString(shouldbeValue))};
            }
        }
    }

    void DebugDB::CheckTables(const Interface::ITable& actual,
                              const Interface::ITable& shouldBe)
    {
        if (actual.GetName() != shouldBe.GetName())
        {
            throw std::runtime_error{
                fmt::format("DebugDB::CheckResult, actual-table-name: {} and "
                            "should-be-table-name: {} must be equal",
                            actual.GetName(), shouldBe.GetName())};
        }
        if (actual.ColumnsCount() != shouldBe.ColumnsCount())
        {
            fmt::println("DebugDB::CheckTables(), actual-list = {}",
                         *actual.ListColumns());
            fmt::println("DebugDB::CheckDatabase(), should-be-list = {}",
                         *shouldBe.ListColumns());

            throw std::runtime_error{
                fmt::format("DebugDB::CheckResult, actual-table-size: {} and "
                            "should-be-table-size: {} must be equal",
                            actual.ColumnsCount(), shouldBe.ColumnsCount())};
        }

        auto columnSize = actual.ColumnsCount();
        for (int columnIndex = 0; columnIndex < columnSize; ++columnIndex)
        {
            auto&& actualColumn   = actual.GetColumn(columnIndex);
            auto&& shouldbeColumn = shouldBe.GetColumn(columnIndex);

            CheckColumn(actualColumn, shouldbeColumn);
        }
    }

    void DebugDB::CheckDatabase(const Interface::IDataBase& actual,
                                const Interface::IDataBase& shouldBe)
    {
        if (actual.GetName() != shouldBe.GetName())
        {
            throw std::runtime_error{fmt::format(
                "DebugDB::CheckResult, actual-database-name: {} and "
                "should-be-database-name: {} must be equal",
                actual.GetName(), shouldBe.GetName())};
        }
        if (actual.TablesCount() != shouldBe.TablesCount())
        {
            fmt::println("DebugDB::CheckDatabase(), actual-list = {}",
                         *actual.ListTables());
            fmt::println("DebugDB::CheckDatabase(), should-be-list = {}",
                         *shouldBe.ListTables());

            throw std::runtime_error{fmt::format(
                "DebugDB::CheckResult, actual-database-size: {} and "
                "should-be-database-size: {} must be equal",
                actual.TablesCount(), shouldBe.TablesCount())};
        }

        auto tablesList = actual.ListTables();
        for (auto&& tableName : *tablesList)
        {
            auto&& actualTable   = actual.GetTable(tableName);
            auto&& shouldbeTable = shouldBe.GetTable(tableName);

            CheckTables(actualTable, shouldbeTable);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
