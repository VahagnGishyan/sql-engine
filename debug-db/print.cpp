
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "debug-db.hpp"

// #include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DebugDB::ColumnToStrList(const Interface::IColumn& column)
        -> std::vector<std::string>
    {
        std::vector<std::string> list;
        list.push_back("column: " + column.GetName());
        list.push_back("column-type: " +
                       Interface::GetDynamicTypeNameAsString(column.GetType()));

        list.push_back(fmt::format("column-size: {}", column.GetSize()));

        const int size = column.GetSize();
        std::vector<std::string> elements;
        for (int index = 0; index < size; ++index)
        {
            elements.push_back(
                Interface::ConvertUDynValueToString(column.GetElement(index)));
        }
        list.push_back(fmt::format("\telements: {}", elements));
        return list;
    }

    auto DebugDB::TableToStrList(const Interface::ITable& table)
        -> std::vector<std::string>
    {
        std::vector<std::string> list;
        list.push_back("table: " + table.GetName());
        list.push_back(fmt::format("table-size: {}", table.ColumnsCount()));

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

    auto DebugDB::DataBaseToStrList(const Interface::IDataBase& database)
        -> std::vector<std::string>
    {
        std::vector<std::string> list;
        list.push_back("database: " + database.GetName());
        list.push_back(
            fmt::format("database-size: {}", database.TablesCount()));

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

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void PrintStrLines(const std::vector<std::string>& data)
    {
        for (auto&& line : data)
        {
            fmt::println(line);
        }
    }

    //////////////////////////////////////////////////////////////////////

    void DebugDB::PrintColumn(const Interface::IColumn& column)
    {
        auto&& columnStr = ColumnToStrList(column);
        PrintStrLines(columnStr);
    }
    void DebugDB::PrintTable(const Interface::ITable& table)
    {
        auto&& tableStr = TableToStrList(table);
        PrintStrLines(tableStr);
    }
    void DebugDB::PrintDataBase(const Interface::IDataBase& database)
    {
        auto&& databaseStr = DataBaseToStrList(database);
        PrintStrLines(databaseStr);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
