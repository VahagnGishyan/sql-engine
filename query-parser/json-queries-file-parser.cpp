
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "json-queries-template.hpp"
#include "parsers.hpp"
#include "query/executors.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryParser
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // class DataBaseReader : public Interface::IDataBaseReader
    // {
    //    protected:
    //     DataBaseReader(const std::string& path) : m_path{path}
    //     {
    //     }

    //    public:
    //     auto Read() const -> Interface::UDataBase override
    //     {
    //         const std::string dbname = Utility::ExtractFileName(m_path);
    //         const std::string tablesDir =
    //             fmt::format("{}/{}/", m_path, TABLES_DIR_NAME);
    //         Interface::TableList tables = GetTablesList(tablesDir);

    //         auto database = DataBase::CreateDataBase(dbname);
    //         for (auto&& table : tables)
    //         {
    //             database->AddTable(std::move(table));
    //         }
    //         return database;
    //     }
    //     virtual auto GetTablesList(const std::string& tablesDir) const
    //         -> Interface::TableList
    //     {
    //         Interface::TableList list{};
    //         if (Utility::IsDirExists(tablesDir))
    //         {
    //             auto&& tablesList = Utility::ListFilesInDir(
    //                 tablesDir, Utility::Option::FullPaths{true});
    //             for (auto&& tableFile : *tablesList)
    //             {
    //                 list.push_back(GetTable(tableFile));
    //             }
    //         }
    //         return list;
    //     }
    //     virtual auto GetTable(const std::string& tablePath) const
    //         -> Interface::UTable
    //     {
    //         Utility::AssertPathAbsolute(tablePath);
    //         Utility::AssertFileExists(tablePath);
    //         Utility::AssertFileExtension(tablePath, ".json");

    //         //////////////////////////////////////////////////////////////

    //         // Create a property tree
    //         boost::property_tree::ptree pt;
    //         // Parse the JSON file
    //         boost::property_tree::read_json(tablePath, pt);

    //         //////////////////////////////////////////////////////////////

    //         std::string tableName = pt.get<std::string>("table-name");
    //         Interface::ColumnInfoList columnInfoList{};
    //         Interface::RowList list;

    //         //////////////////////////////////////////////////////////////

    //         // Access columns
    //         auto&& columns = pt.get_child("columns");
    //         AccessColumns(columnInfoList, columns);

    //         // Access rows
    //         auto&& rowsJS = pt.get_child("rows");
    //         AccessRows(list, columnInfoList, rowsJS);

    //         //////////////////////////////////////////////////////////////

    //         auto&& rotable = DataBase::CreateRowOrientedTable(
    //             std::move(tableName), std::move(columnInfoList),
    //             std::move(list));

    //         return rotable->CreateTable();
    //     }
    //     virtual void AccessColumns(
    //         Interface::ColumnInfoList& columnInfoList,
    //         const boost::property_tree::ptree& columns) const
    //     {
    //         for (auto&& column : columns)
    //         {
    //             auto&& columnName    =
    //             column.second.get<std::string>("name"); auto&& strColumnType
    //             = column.second.get<std::string>("type"); auto&& columnType =
    //                 Interface::ConvertStringToDynamicType(strColumnType);
    //             columnInfoList.emplace_back(columnName, columnType);
    //         }
    //     }
    //     virtual void AccessRows(Interface::RowList& list,
    //                             const Interface::ColumnInfoList&
    //                             columnInfoList, const
    //                             boost::property_tree::ptree& rowsJS) const
    //     {
    //         for (auto&& row : rowsJS)
    //         {
    //             Interface::Row rowNode{};
    //             rowNode.reserve(columnInfoList.size());
    //             int columnIndex = -1;
    //             for (const auto& cell : row.second)
    //             {
    //                 ++columnIndex;

    //                 auto type  = columnInfoList[columnIndex].type;
    //                 auto value = GetValue(cell.second, type);

    //                 rowNode.push_back(std::move(value));
    //             }
    //             list.push_back(std::move(rowNode));
    //         }
    //     }
    //     virtual auto GetValue(const boost::property_tree::ptree& value,
    //                           const Interface::DynamicType& type) const
    //         -> Interface::UDynamicValue
    //     {
    //         auto&& strvalue = value.get_value<std::string>();
    //         if ((strvalue == "nullptr") || (strvalue == "null"))
    //         {
    //             return nullptr;
    //         }

    //         Interface::DynamicValue dvalue;
    //         switch (type)
    //         {
    //             case Interface::DynamicType::Int:
    //                 dvalue = value.get_value<Interface::GetDynamicType<
    //                     Interface::DynamicType::Int>::type>();
    //                 break;
    //             case Interface::DynamicType::Double:
    //                 dvalue = value.get_value<Interface::GetDynamicType<
    //                     Interface::DynamicType::Double>::type>();
    //                 break;
    //             case Interface::DynamicType::String:
    //                 dvalue = value.get_value<Interface::GetDynamicType<
    //                     Interface::DynamicType::String>::type>();
    //                 break;
    //             default:
    //                 throw std::logic_error{"Unknown DynamicValue type"};
    //         }
    //         return Interface::CreateUDynValue(dvalue);
    //     }

    //    public:
    //     static auto Create(const std::string& path)
    //         -> Interface::UDataBaseReader
    //     {
    //         Utility::AssertPathAbsolute(path);
    //         Utility::AssertDirExists(path);

    //         Interface::UDataBaseReader ureader{new DataBaseReader{path}};
    //         return (ureader);
    //     }

    //    protected:
    //     std::string m_path;
    // };

    /*
    # INSERT INTO employees (first_name, last_name, job_title, salary)
    # VALUES ('John', 'Doe', 'Software Engineer', 75000);
    #    """
    */

    // auto GetTable(const std::string& tablePath) const -> Interface::UTable
    // {
    //     //////////////////////////////////////////////////////////////

    //     std::string tableName = pt.get<std::string>("table-name");
    //     Interface::ColumnInfoList columnInfoList{};
    //     Interface::RowList list;

    //     //////////////////////////////////////////////////////////////

    //     // Access columns
    //     auto&& columns = pt.get_child("columns");
    //     AccessColumns(columnInfoList, columns);

    //     // Access rows
    //     auto&& rowsJS = pt.get_child("rows");
    //     AccessRows(list, columnInfoList, rowsJS);

    //     //////////////////////////////////////////////////////////////

    //     auto&& rotable = DataBase::CreateRowOrientedTable(
    //         std::move(tableName), std::move(columnInfoList),
    //         std::move(list));

    //     return rotable->CreateTable();
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateCondition(const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        return nullptr;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateQuerySelectFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        Interface::ColumnNameList columns{};
        for (const auto& column : arguments.get_child(OP_SELECT_COLUMNS))
        {
            columns.push_back(column.second.get_value<std::string>());
        }

        const std::string tableName =
            arguments.get<std::string>(OP_SELECT_FROM);

        auto&& condition =
            CreateCondition(arguments.get_child(OP_SELECT_WHERE));

        return Query::CreateQuery(
            tableName,
            Query::CreateOpSelect(std::move(columns), std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryInsertIntoFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        const std::string tableName =
            arguments.get<std::string>(OP_INSERT_INTO_TABLE);

        Query::InsertIntoData rows{};
        for (const auto& column : arguments.get_child(OP_INSERT_INTO_ROW))
        {
            std::string columnName =
                column.second.get<std::string>(OP_INSERT_INTO_COLUMN_NAME);
            std::string columnType =
                column.second.get<std::string>(OP_INSERT_INTO_COLUMN_TYPE);

            auto dynType = Interface::ConvertStringToDynamicType(columnType);

            for (const auto& value :
                 column.second.get_child(OP_INSERT_INTO_COLUMN_VALUES))
            {
                if (dynType == Interface::DynamicType::Int)
                {
                    Interface::GetDynamicType<Interface::DynamicType::Int>::type
                        cellValue = value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::Int>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
                if (dynType == Interface::DynamicType::Double)
                {
                    Interface::GetDynamicType<
                        Interface::DynamicType::Double>::type cellValue =
                        value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::Double>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
                if (dynType == Interface::DynamicType::String)
                {
                    Interface::GetDynamicType<
                        Interface::DynamicType::String>::type cellValue =
                        value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::String>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
            }
        }

        return Query::CreateQuery(tableName,
                                  Query::CreateOpInsertInto(std::move(rows)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryUpdateFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        Query::UpdateData data{};
        const std::string tableName =
            arguments.get<std::string>(OP_UPDATE_TABLE);

        for (const auto& cell : arguments.get_child(OP_INSERT_INTO_ROW))
        {
            std::string columnName =
                cell.second.get<std::string>(OP_UPDATE_CELL_COLUMN);
            std::string columnType =
                cell.second.get<std::string>(OP_UPDATE_CELL_TYPE);
            std::string value =
                cell.second.get<std::string>(OP_UPDATE_CELL_VALUE);

            auto dynType = Interface::ConvertStringToDynamicType(columnType);
            if (dynType == Interface::DynamicType::Int)
            {
                Interface::GetDynamicType<Interface::DynamicType::Int>::type
                    cellValue    = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::Int>::type>("");
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
            if (dynType == Interface::DynamicType::Double)
            {
                Interface::GetDynamicType<Interface::DynamicType::Double>::type
                    cellValue    = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::Double>::type>("");
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
            if (dynType == Interface::DynamicType::String)
            {
                Interface::GetDynamicType<Interface::DynamicType::String>::type
                    cellValue    = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::String>::type>("");
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
        }

        auto&& condition =
            CreateCondition(arguments.get_child(OP_UPDATE_WHERE));

        return Query::CreateQuery(
            tableName,
            Query::CreateOpUpdate(std::move(data), std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryDeleteFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        const std::string tableName =
            arguments.get<std::string>(OP_DELETE_FROM);
        auto&& condition =
            CreateCondition(arguments.get_child(OP_DELETE_WHERE));

        return Query::CreateQuery(tableName,
                                  Query::CreateOpDelete(std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateQueryExecutorFromJSONFile(
        const std::string& operation,
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        if (operation == OP_SELECT)
        {
            return CreateQuerySelectFromJSONFile(arguments);
        }
        if (operation == OP_INSERT_INTO)
        {
            return CreateQueryInsertIntoFromJSONFile(arguments);
        }
        if (operation == OP_UPDATE)
        {
            return CreateQueryUpdateFromJSONFile(arguments);
        }
        if (operation == OP_DELETE)
        {
            return CreateQueryDeleteFromJSONFile(arguments);
        }

        throw std::logic_error{
            fmt::format("CreateQueryExecutorFromJSONFile: Unknown operation {}",
                        operation)};
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryExecutorFromJSONFile(const std::string& filepath)
        -> Interface::UQuery
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(filepath, pt);

        std::string operation = pt.get<std::string>(QUERY_OPERATION);
        auto&& arguments      = pt.get_child(QUERY_ARGUMENTS);

        return CreateQueryExecutorFromJSONFile(operation, arguments);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateFromJSONFile(const std::string& filepath) -> Interface::UQuery
    {
        Utility::AssertFileExtension(filepath, ".json");
        Utility::AssertFileExists(filepath);
        return CreateQueryExecutorFromJSONFile(filepath);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryParser

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
