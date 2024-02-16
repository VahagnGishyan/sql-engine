
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "cli-operations.hpp"

#include <fmt/ranges.h>

#include "debug-db/debug-db.hpp"
#include "local-database/local-database.hpp"
#include "query-parser/parsers.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::CLI
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::Help(std::vector<std::string> data) -> UOperation
    {
        class Help : public Operation
        {
           public:
            Help(std::vector<std::string> data) : m_data{std::move(data)}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                return m_data;
            }

           protected:
            std::vector<std::string> m_data;
        };

        return std::make_unique<Help>(std::move(data));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateOp::WorkDir() -> UOperation
    {
        class WorkDir : public Operation
        {
           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                std::vector<std::string> data;
                auto&& workdir = db.GetWorkDirPath();
                if (workdir.size())
                {
                    data.push_back(fmt::format("database-work-dir: {}", workdir));
                }
                else
                {
                    data.push_back("Database is not connected yet.");
                }
                return data;
            }
        };

        return std::make_unique<WorkDir>();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::InitAt(const std::string& path) -> UOperation
    {
        class InitAt : public Operation
        {
           public:
            InitAt(const std::string& path) : m_path{path}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.Init(m_path);
                return std::vector<std::string>{"Initialization succeed!"};
            }

           protected:
            std::string m_path;
        };

        return std::make_unique<InitAt>(path);
    }
    auto CreateOp::ConnectTo(const std::string& path) -> UOperation
    {
        class ConnectTo : public Operation
        {
           public:
            ConnectTo(const std::string& path) : m_path{path}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.Connect(m_path);
                return std::vector<std::string>{"Connection succeed!"};
            }

           protected:
            std::string m_path;
        };

        return std::make_unique<ConnectTo>(path);
    }
    auto CreateOp::Disconnect() -> UOperation
    {
        class Disconnect : public Operation
        {
           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.Disconnect();
                return std::vector<std::string>{
                    "Database has been successfully disconnected!"};
            }
        };

        return std::make_unique<Disconnect>();
    }
    auto CreateOp::DisconnectPath(const std::string& path) -> UOperation
    {
        class DisconnectPath : public Operation
        {
           public:
            DisconnectPath(const std::string& path) : m_path{path}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.Disconnect(m_path);
                return std::vector<std::string>{
                    "Database has been successfully disconnected!"};
            }

           protected:
            std::string m_path;
        };

        return std::make_unique<DisconnectPath>(path);
    }
    auto CreateOp::SaveAt(const std::string& path) -> UOperation
    {
        class SaveAt : public Operation
        {
           public:
            SaveAt(const std::string& path) : m_path{path}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.SaveAt(m_path);
                return std::vector<std::string>{
                    "Database has been successfully disconnected!"};
            }

           protected:
            std::string m_path;
        };

        return std::make_unique<SaveAt>(path);
    }
    auto CreateOp::Drop() -> UOperation
    {
        class Drop : public Operation
        {
           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.Drop();
                return std::vector<std::string>{
                    "Database has been successfully droped!"};
            }
        };

        return std::make_unique<Drop>();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::Rename(const std::string& newname) -> UOperation
    {
        class Rename : public Operation
        {
           public:
            Rename(const std::string& name) : m_name{name}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.SetName(m_name);
                return std::vector<std::string>{
                    "Database has been successfully renamed!"};
            }

           protected:
            std::string m_name;
        };

        return std::make_unique<Rename>(newname);
    }
    auto CreateOp::AddTable(const std::string& tableName) -> UOperation
    {
        class AddTable : public Operation
        {
           public:
            AddTable(const std::string& name) : m_tableName{name}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto table = LocalDataBase::CreateTable(m_tableName);
                db.AddTable(std::move(table));
                auto listDataBase = ListTables();
                return listDataBase->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
        };

        return std::make_unique<AddTable>(tableName);
    }
    auto CreateOp::RemoveTable(const std::string& tableName) -> UOperation
    {
        class RemoveTable : public Operation
        {
           public:
            RemoveTable(const std::string& name) : m_tableName{name}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.RemoveTable(m_tableName);
                auto listDataBase = ListTables();
                return listDataBase->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
        };

        return std::make_unique<RemoveTable>(tableName);
    }
    auto CreateOp::RenameTable(const std::string& tableName,
                               const std::string& newname) -> UOperation
    {
        class RenameTable : public Operation
        {
           public:
            RenameTable(const std::string& name, const std::string& newname) :
                m_tableName{name}, m_newName{newname}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                db.RenameTable(m_tableName, m_newName);
                auto listDataBase = CreateOp::ListTables();
                return listDataBase->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
            std::string m_newName;
        };

        return std::make_unique<RenameTable>(tableName, newname);
    }
    auto CreateOp::ListTables() -> UOperation
    {
        class Drop : public Operation
        {
           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto listDataBase = CreateOp::ListTables();
                return listDataBase->ExecuteFor(db);
            }
        };

        return std::make_unique<Drop>();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::TableAddColumn(const std::string& tableName,
                                  const std::string& columnName,
                                  const std::string& columnType) -> UOperation
    {
        class TableAddColumn : public Operation
        {
           public:
            TableAddColumn(const std::string& tableName,
                           const std::string& columnName,
                           const std::string& columnType) :
                m_tableName{tableName},
                m_columnName{columnName},
                m_columnType{columnType}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto type = Interface::ConvertStringToDynamicType(m_columnType);
                auto&& table = db.GetTable(m_tableName);
                table.AddColumn(
                    LocalDataBase::CreateColumn(m_columnName, type));

                auto list = CreateOp::TableListColumns(m_tableName);
                return list->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
            std::string m_columnName;
            std::string m_columnType;
        };

        return std::make_unique<TableAddColumn>(tableName, columnName,
                                                columnType);
    }
    auto CreateOp::TableDropColumn(const std::string& tableName,
                                   const std::string& columnName) -> UOperation
    {
        class TableDropColumn : public Operation
        {
           public:
            TableDropColumn(const std::string& tableName,
                            const std::string& columnName) :
                m_tableName{tableName}, m_columnName{columnName}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto&& table = db.GetTable(m_tableName);
                table.RemoveColumn(m_columnName);

                auto list = CreateOp::TableListColumns(m_tableName);
                return list->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
            std::string m_columnName;
        };

        return std::make_unique<TableDropColumn>(tableName, columnName);
    }
    auto CreateOp::TableRenameColumn(const std::string& tableName,
                                     const std::string& columnName,
                                     const std::string& newColumnName)
        -> UOperation
    {
        class TableRenameColumn : public Operation
        {
           public:
            TableRenameColumn(const std::string& tableName,
                              const std::string& columnName,
                              const std::string& newColumnName) :
                m_tableName{tableName}, m_columnName{columnName}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto&& table = db.GetTable(m_tableName);
                table.RenameColumn(m_columnName, m_columnNewName);

                auto list = CreateOp::TableListColumns(m_tableName);
                return list->ExecuteFor(db);
            }

           protected:
            std::string m_tableName;
            std::string m_columnName;
            std::string m_columnNewName;
        };

        return std::make_unique<TableRenameColumn>(tableName, columnName,
                                                   newColumnName);
    }
    auto CreateOp::TableListColumns(const std::string& tableName) -> UOperation
    {
        class TableListColumns : public Operation
        {
           public:
            TableListColumns(const std::string& tableName) :
                m_tableName{tableName}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto&& table = db.GetTable(m_tableName);
                auto list    = table.ListColumns();
                return std::vector<std::string>{fmt::format(
                    "table: {}, list-columns: {}", m_tableName, *list)};
            }

           protected:
            std::string m_tableName;
        };

        return std::make_unique<TableListColumns>(tableName);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::Execute(const std::string& path) -> UOperation
    {
        class Execute : public Operation
        {
           public:
            Execute(const std::string& path) : m_path{path}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto query = QueryParser::CreateFromJSONFile(m_path);
                query->Execute(db);

                auto tableName = query->GetTableName();
                auto print = CreateOp::PrintTable(tableName);
                return print->ExecuteFor(db);
            }

           protected:
            std::string m_path;
        };

        return std::make_unique<Execute>(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateOp::PrintDataBase() -> UOperation
    {
        class PrintDataBase : public Operation
        {
           public:
            PrintDataBase()
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                return DebugDB::DataBaseToStrList(db);
            }
        };

        return std::make_unique<PrintDataBase>();
    }
    auto CreateOp::PrintTable(const std::string& tableName) -> UOperation
    {
        class PrintTable : public Operation
        {
           public:
            PrintTable(const std::string& tableName) : m_tableName{tableName}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto&& table = db.GetTable(m_tableName);
                return DebugDB::TableToStrList(table);
            }

           protected:
            std::string m_tableName;
        };

        return std::make_unique<PrintTable>(tableName);
    }
    auto CreateOp::PrintColumn(const std::string& tableName,
                               const std::string& columnName) -> UOperation
    {
        class PrintTable : public Operation
        {
           public:
            PrintTable(const std::string& tableName,
                       const std::string& columnName) :
                m_tableName{tableName}, m_columnName{columnName}
            {
            }

           public:
            auto ExecuteFor(Interface::IConnectDataBase& db) const
                -> std::vector<std::string> override
            {
                auto&& table = db.GetTable(m_tableName);
                auto&& column = table.GetColumn(m_columnName);
                return DebugDB::ColumnToStrList(column);
            }

           protected:
            std::string m_tableName;
            std::string m_columnName;
        };

        return std::make_unique<PrintTable>(tableName, columnName);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
