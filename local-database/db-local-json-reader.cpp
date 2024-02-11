
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "database/database.hpp"
#include "db-local-json-stream.hpp"
#include "db-local-json-struct.hpp"
#include "interface/i-row-oriented-table.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::LocalDataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DataBaseReader : public Interface::IDataBaseReader
    {
       protected:
        DataBaseReader(const std::string& path) : m_path{path}
        {
        }

       public:
        auto Read() const -> Interface::UDataBase override
        {
            const std::string dbname = Utility::ExtractFileName(m_path);
            const std::string tablesDir =
                fmt::format("{}/{}/", m_path, TABLES_DIR_NAME);
            Interface::TableList tables = GetTablesList(tablesDir);

            auto database = DataBase::CreateDataBase(dbname);
            for (auto&& table : tables)
            {
                database->AddTable(std::move(table));
            }
            return database;
        }
        virtual auto GetTablesList(const std::string& tablesDir) const
            -> Interface::TableList
        {
            Interface::TableList list{};
            if (Utility::IsDirExists(tablesDir))
            {
                auto&& tablesList = Utility::ListFilesInDir(
                    tablesDir, Utility::Option::FullPaths{true});
                for (auto&& tableFile : *tablesList)
                {
                    list.push_back(GetTable(tableFile));
                }
            }
            return list;
        }
        virtual auto GetTable(const std::string& tablePath) const
            -> Interface::UTable
        {
            Utility::AssertPathAbsolute(tablePath);
            Utility::AssertFileExists(tablePath);
            Utility::AssertFileExtension(tablePath, ".json");

            //////////////////////////////////////////////////////////////

            // Create a property tree
            boost::property_tree::ptree pt;
            // Parse the JSON file
            boost::property_tree::read_json(tablePath, pt);

            //////////////////////////////////////////////////////////////

            std::string tableName = pt.get<std::string>("table-name");
            Interface::ColumnInfoList columnInfoList{};
            Interface::RowList list;

            //////////////////////////////////////////////////////////////

            // Access columns
            auto&& columns = pt.get_child("columns");
            AccessColumns(columnInfoList, columns);

            // Access rows
            auto&& rowsJS = pt.get_child("rows");
            AccessRows(list, columnInfoList, rowsJS);

            //////////////////////////////////////////////////////////////

            auto&& rotable = DataBase::CreateRowOrientedTable(
                std::move(tableName), std::move(columnInfoList),
                std::move(list));

            return rotable->CreateTable();
        }
        virtual void AccessColumns(
            Interface::ColumnInfoList& columnInfoList,
            const boost::property_tree::ptree& columns) const
        {
            for (auto&& column : columns)
            {
                auto&& columnName    = column.second.get<std::string>("name");
                auto&& strColumnType = column.second.get<std::string>("type");
                auto&& columnType =
                    Interface::ConvertStringToDynamicType(strColumnType);
                columnInfoList.emplace_back(columnName, columnType);
            }
        }
        virtual void AccessRows(Interface::RowList& list,
                                const Interface::ColumnInfoList& columnInfoList,
                                const boost::property_tree::ptree& rowsJS) const
        {
            for (auto&& row : rowsJS)
            {
                Interface::Row rowNode{};
                rowNode.reserve(columnInfoList.size());
                int columnIndex = -1;
                for (const auto& cell : row.second)
                {
                    ++columnIndex;

                    auto type  = columnInfoList[columnIndex].type;
                    auto value = GetValue(cell.second, type);

                    rowNode.push_back(std::move(value));
                }
                list.push_back(std::move(rowNode));
            }
        }
        virtual auto GetValue(const boost::property_tree::ptree& value,
                              const Interface::DynamicType& type) const
            -> Interface::UDynamicValue
        {
            auto&& strvalue = value.get_value<std::string>();
            if ((strvalue == "nullptr") || (strvalue == "null"))
            {
                return nullptr;
            }

            Interface::DynamicValue dvalue;
            switch (type)
            {
                case Interface::DynamicType::Int:
                    dvalue = value.get_value<Interface::GetDynamicType<
                        Interface::DynamicType::Int>::type>();
                    break;
                case Interface::DynamicType::Double:
                    dvalue = value.get_value<Interface::GetDynamicType<
                        Interface::DynamicType::Double>::type>();
                    break;
                case Interface::DynamicType::String:
                    dvalue = value.get_value<Interface::GetDynamicType<
                        Interface::DynamicType::String>::type>();
                    break;
                default:
                    throw std::logic_error{"Unknown DynamicValue type"};
            }
            return Interface::CreateUDynValue(dvalue);
        }

       public:
        static auto Create(const std::string& path)
            -> Interface::UDataBaseReader
        {
            Utility::AssertPathAbsolute(path);
            Utility::AssertDirExists(path);

            Interface::UDataBaseReader ureader{new DataBaseReader{path}};
            return (ureader);
        }

       protected:
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDBLocalJSONReader(const std::string& path)
        -> Interface::UDataBaseReader
    {
        return DataBaseReader::Create(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
