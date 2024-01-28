
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/optional/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "database/database.hpp"
#include "db-local-json-stream.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DataBaseJSONWriter : public Interface::IDataBaseWriter
    {
       protected:
        DataBaseJSONWriter(const std::string& path) : m_path{path}
        {
        }

       public:
        void Write(const Interface::IDataBase& database) const override
        {
            auto workdir = GetWorkDir(database);

            PrepareWorkDirectory(workdir);
            WriteDataBaseInformation(workdir, database);
            WriteTables(workdir, database);
        }

       public:
        static auto Create(const std::string& path)
            -> Interface::UDataBaseWriter
        {
            Utility::AssertPathAbsolute(path);
            Interface::UDataBaseWriter uwriter{new DataBaseJSONWriter{path}};
            return (uwriter);
        }

       protected:
        virtual auto GetWorkDir(const Interface::IDataBase& database) const
            -> const std::string
        {
            return fmt::format("{}/{}", m_path, database.GetName());
        }
        virtual void PrepareWorkDirectory(const std::string& path) const
        {
            Utility::MakeDir(path, Utility::Option::ExistOk{true},
                             Utility::Option::CreateBaseDirectory{true});
        }
        virtual void WriteInFile(const boost::property_tree::ptree& pt,
                                 const std::string& jsonfile) const
        {
            Utility::AssertPathAbsolute(jsonfile);
            Utility::CheckFileExtension(jsonfile, ".json");
            Utility::MakeDir(Utility::GetBaseDir(jsonfile),
                             Utility::Option::ExistOk{true},
                             Utility::Option::CreateBaseDirectory{true});

            std::ostringstream oss;
            boost::property_tree::json_parser::write_json(oss, pt);

            std::ofstream outputFile(jsonfile);

            Utility::Assert(
                outputFile.is_open(),
                fmt::format("DataBaseJSONWriter::Write::"
                            "WriteDataBaseInformation, can't open file {}",
                            jsonfile));

            outputFile << oss.str();
        }
        virtual void WriteDataBaseInformation(
            const std::string& workDir,
            const Interface::IDataBase& database) const
        {
            //////////////////////////////////////////////////////////////

            const std::string databaseName = database.GetName();
            boost::property_tree::ptree pt;
            pt.put("database-name", databaseName);
            pt.put("access", "public");

            //////////////////////////////////////////////////////////////

            std::string jsonpath =
                fmt::format("{}/{}.json", workDir, databaseName);

            //////////////////////////////////////////////////////////////

            WriteInFile(pt, jsonpath);
        }
        virtual void WriteTables(const std::string& workDir,
                                 const Interface::IDataBase& database) const
        {
            auto&& tableList = database.ListTables();
            for (auto&& tableName : *tableList)
            {
                auto&& table   = database.GetTable(tableName);
                auto&& rotable = DataBase::CreateRowOrientedTable(table);
                WriteTable(workDir, *rotable);
            }
        }
        virtual void WriteTable(const std::string& workDir,
                                const Interface::IRowOrientedTable& table) const
        {
            boost::property_tree::ptree root;
            boost::property_tree::ptree columns;
            boost::property_tree::ptree rows;

            //////////////////////////////////////////////////////////////

            AddTableInfo(root, table);
            AddColumns(columns, table);
            AddRows(rows, table);

            //////////////////////////////////////////////////////////////

            root.add_child("columns", columns);
            root.add_child("rows", rows);

            //////////////////////////////////////////////////////////////

            std::string jsonpath =
                fmt::format("{}/tables/{}.json", workDir, table.GetTableName());

            WriteInFile(root, jsonpath);
        }

        virtual void AddTableInfo(
            boost::property_tree::ptree& root,
            const Interface::IRowOrientedTable& table) const
        {
            root.put("table-name", table.GetTableName());
        }

        virtual void AddColumns(boost::property_tree::ptree& root,
                                const Interface::IRowOrientedTable& table) const
        {
            auto&& columnsInfo = table.GetColumnInfoList();
            for (auto&& columnInfo : columnsInfo)
            {
                boost::property_tree::ptree columnsNode;
                columnsNode.put("name", columnInfo.name);
                columnsNode.put("type", Interface::GetDynamicTypeNameAsString(
                                            columnInfo.type));

                root.push_back(std::make_pair("", columnsNode));
            }
        }

        virtual void AddRows(boost::property_tree::ptree& root,
                             const Interface::IRowOrientedTable& table) const
        {
            auto rowCount      = table.RowsCount();
            auto columnsCount  = table.ColumnsCount();
            auto&& columnsInfo = table.GetColumnInfoList();

            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
            {
                boost::property_tree::ptree rowNode;
                for (int columnIndex = 0; columnIndex < columnsCount;
                     ++columnIndex)
                {
                    auto&& value = table.GetValue(rowIndex, columnIndex);
                    rowNode.push_back(std::make_pair(
                        "", boost::property_tree::ptree(
                                Interface::ConvertUDynValueToString(
                                    value, columnsInfo[columnIndex].type))));
                }
                root.push_back(std::pair("", rowNode));
            }
        }

       protected:
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDBLocalJSONWriter(const std::string& path)
        -> Interface::UDataBaseWriter
    {
        return DataBaseJSONWriter::Create(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
