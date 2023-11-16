
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "db-manager.hpp"

#include <fmt/core.h>

#include <algorithm>

#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Manager::GetInfo() const -> const Interface::WDBObjectInfo
    {
        return m_info;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Manager::Connect(const Interface::IDBManagerInit& data)
    {
        Interface::NotImplYet("db-manager.cpp, Manager::Connect(...)");
    }
    void Manager::Disconnect()
    {
        Interface::NotImplYet("db-manager.cpp, Manager::Disconnect(...)");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Manager::DatabaseExists(const Interface::IDataBaseID& dbid) const -> bool
    {
        auto&& opdb = GetDatabaseOptional(dbid);
        return (opdb != std::nullopt);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Manager::ListDatabase() const -> Interface::UDataBaseIDList
    {
        auto&& dbidlist = std::make_unique<Interface::DataBaseIDList>();
        for (auto&& db : m_databases)
        {
            dbidlist->push_back(db->GetID());
        }
        return std::move(dbidlist);
    }

    auto Manager::ListConnectedDatabase() const -> Interface::UDataBaseIDList
    {
        auto&& dbidlist = std::make_unique<Interface::DataBaseIDList>();
        for (auto&& db : m_databases)
        {
            if (db->IsConnected())
            {
                dbidlist->push_back(db->GetID());
            }
        }
        return std::move(dbidlist);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Manager::AssertDBExists(const Interface::IDataBaseID& dbid) const
    {
        Utility::Assert(DatabaseExists(dbid),
                        fmt::format("Database with the name: {} does not exists.", dbid.GetName()));
    }
    void Manager::AssertDBNotExists(const Interface::IDataBaseID& dbid) const
    {
        Utility::Assert(!DatabaseExists(dbid), fmt::format("Database with the same name: {} exists.", dbid.GetName()));
    }
    void Manager::AssertDBConnected(const Interface::IDataBaseID& dbid) const
    {
        Utility::Assert(DatabaseExists(dbid) && DatabaseConnected(dbid),
                        fmt::format("Database with the name: {} is not connected.", dbid.GetName()));
    }
    void Manager::AssertDBNotConnected(const Interface::IDataBaseID& dbid) const
    {
        Utility::Assert(DatabaseExists(dbid) && !DatabaseConnected(dbid),
                        fmt::format("Database with the name: {} is connected.", dbid.GetName()));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Manager::CreateDatabase(const Interface::IDataBaseID& dbid) -> Interface::WDataBase
    {
        Interface::NotImplYet("db-manager.cpp, Manager::CreateDatabase(...)");
        return Interface::WDataBase{};
        //     def create_database(self, name):
        //         # Create a new database with the given name
        //         self.assert_db_not_exists(name)
        //         new_database = Database.create(name, self.get_work_dir())
        //         self.databases.append(name)
    }

    void Manager::ConnectDatabase(const Interface::IDataBaseID& data)
    {
        Interface::NotImplYet("db-manager.cpp, Manager::ConnectDatabase(...)");
        //     def connect(self, name):
        //         self.assert_db_not_connected(name)
        //         database = Database.create(name, self.get_work_dir(),
        //         connect=True) self.connected_dbs[name] = database return database
    }

    auto Manager::DatabaseConnected(const Interface::IDataBaseID& dbid) const -> bool
    {
        auto&& opdb = GetDatabaseOptional(dbid);
        if (opdb == std::nullopt)
        {
            return false;
        }
        auto&& value = opdb.value();
        auto&& db    = value.lock();
        return db->IsConnected();
    }

    auto Manager::GetDatabase(const Interface::IDataBaseID& dbid) -> Interface::WDataBase
    {
        AssertDBExists(dbid);
        auto&& opdb = GetDatabaseOptional(dbid);
        return *opdb;
    }

    void Manager::DisconnectDatabase(const Interface::IDataBaseID& dbid)
    {
        Interface::NotImplYet("db-manager.cpp, Manager::DisconnectDatabase(...)");
        //     def disconnect(self, dbparam):
        //         database = None
        //         name = None
        //         if isinstance(dbparam, str):
        //             name = dbparam
        //             self.assert_db_connected(name)
        //             database = self.connected_dbs[name]
        //         elif isinstance(dbparam, Database):
        //             database = dbparam
        //             name = database.get_name()
        //             self.assert_db_connected(name)

        //         database.disconnect()
        //         del self.connected_dbs[name]
    }

    void Manager::DropDatabase(const Interface::IDataBaseID& dbid)
    {
        Interface::NotImplYet("db-manager.cpp, Manager::DropDatabase(...)");
        //     def drop_database(self, name):
        //         self.assert_db_exists(name)
        //         self.assert_db_not_connected(name)
        //         database = Database.create(name, self.get_work_dir())
        //         Database.destroy(database)
        //         self.databases.remove(name)
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Manager::GetDatabaseOptional(const Interface::IDataBaseID& dbid) const -> std::optional<Interface::WDataBase>
    {
        const auto end = m_databases.end();
        auto itr       = std::find_if(m_databases.begin(), end,
                                      [&dbid](const Interface::ShDataBase db)
                                      {
                                    return (db->GetDataBaseID().GetName() == dbid.GetName());
                                });
        if (itr == end)
        {
            return std::nullopt;
        }

        return std::make_optional<Interface::WDataBase>((*itr));
    }

    //////////////////////////////////////////////////////////////////////

    void Manager::DisconnectAllDataBases()
    {
        for (auto&& db : m_databases)
        {
            if (db->IsConnected())
            {
                db->Disconnect();
            }
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DoSomething()
    {
        Logging::Signal("Hello from db-manager.");
    }

}  // namespace SQLEngine::DBLib::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
