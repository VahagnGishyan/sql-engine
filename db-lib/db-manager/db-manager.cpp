
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "db-manager.hpp"

#include "logging/logging.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DoSomething()
    {
        Logging::Signal("Hello from db-manager.");
    }

    // auto Manager::GetWorkDir() const -> const std::string
    // {
    //     return m_info->GetWorkDir();
    // }

    // //////////////////////////////////////////////////////////////////////
    // //                                                                  //
    // //////////////////////////////////////////////////////////////////////

    // auto Manager::DatabaseExists(const Interface::IDataBaseID& dbid) const
    //     -> bool
    // {
    //     auto&& opdb = GetDatabaseOptional(dbid);
    //     return (opdb != std::nullopt);
    // }

    // auto Manager::DatabaseConnected(const Interface::IDataBaseID& dbid) const
    //     -> bool
    // {
    //     auto&& opdb = GetDatabaseOptional(dbid);
    //     if (opdb == std::nullopt)
    //     {
    //         return false;
    //     }
    //     return true;
    // }

    // //////////////////////////////////////////////////////////////////////
    // //                                                                  //
    // //////////////////////////////////////////////////////////////////////

    // //     def list_database(self):
    // //         return list(self.databases)

    // //     def list_connected_database(self):
    // //         connected_dbs_names = list(self.connected_dbs.keys())
    // //         return connected_dbs_names
    // auto Manager::ListDatabase() const -> Interface:: UDataBaseIDList
    // {
    //     auto&& dbidlist = std::make_unique<Interface:: DataBaseIDList>();
    //     for (auto&& db : m_databases)
    //     {
    //         dbidlist->push_back(db->GetID());
    //     }
    //     return std::move(dbidlist);
    // }
    // auto Manager::ListConnectedDatabase() const -> Interface::
    // UDataBaseIDList
    // {
    //     auto&& dbidlist = std::make_unique<Interface:: DataBaseIDList>();
    //     for (auto&& db : m_databases)
    //     {
    //         if (db->IsConnected())
    //         {
    //             dbidlist->push_back(db->GetID());
    //         }
    //     }
    //     return std::move(dbidlist);
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // def assert_db_exists(self, name):

    // def assert_db_not_exists(self, name):
    //     if self.database_exists(name):
    //         raise ValueError(
    //             f"Dtabase with the same name: {name} exists.")

    // def assert_db_connected(self, name):
    //     self.assert_db_exists(name)
    //     if not self.database_connected(name):
    //         raise ValueError(
    //             f"Database with the name: {name} is not connected.")

    // def assert_db_not_connected(self, name):
    //     self.assert_db_exists(name)
    //     if self.database_connected(name):
    //         raise ValueError(
    //             f"Database with the name: {name} is connected.")

    // void Manager::AssertDBExists(const Interface::IDataBaseID& dbid) const
    // {
    //     Utility::Assert(
    //         DatabaseExists(dbid),
    //         fmt::format("Database with the name: {} does not exists.",
    //                     dbid.GetName()));
    // }
    // void Manager::AssertDBNotExists(const Interface::IDataBaseID& dbid) const
    // {
    // }
    // void Manager::AssertDBConnected(const Interface::IDataBaseID& dbid) const
    // {
    // }
    // void Manager::AssertDBNotConnected(const Interface::IDataBaseID& dbid)
    // const
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // void Manager::Connect(const IDBManagerInit& data)
    // {
    // }
    // void Manager::Disconnect()
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // auto Manager::CreateDatabase(const Interface::IDataBaseID& dbid)
    //     -> UDataBase
    // {
    // }
    // auto Manager::GetDatabase(const Interface::IDataBaseID& dbid) ->
    // IDataBase&
    // {
    // }
    // void Manager::DropDatabase(const Interface::IDataBaseID& dbid)
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // auto Manager::GetDatabaseOptional(const Interface::IDataBaseID& dbid)
    // const
    //     -> std::optional<IDataBase&>
    // {
    //     const auto end = m_databases.end();
    //     auto itr       = std::find_if(
    //         m_databases.begin(), end,
    //         [&dbid](const IDataBase& db)
    //         {
    //             return (db.GetDataBaseID().GetName() == dbid.GetName());
    //         });
    //     if (itr == end)
    //     {
    //         return std::nullopt;
    //     }

    //     return std::make_optional<IDataBase&>(*(*itr));
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // #############################################################
    // #                                                           #
    // #############################################################

    // class DatabaseManager:
    //     def __init__(self, path=None, file_manager=FileManager()):
    //         self.file_manager = file_manager

    //         if path is None:
    //             path = self.file_manager.get_db_default_dir()
    //         if not utfile.is_path_exists(path):
    //             utfile.mkdir(path)
    //         utfile.assert_dir_exists(path)
    //         self.path = path

    //         self.databases: list[str] = utfile.list_dirs_in_dir(self.path)
    //         self.connected_dbs: map = {}

    //     #########################################################

    //     #########################################################

    //     #########################################################

    //     #########################################################

    //     def create_database(self, name):
    //         # Create a new database with the given name
    //         self.assert_db_not_exists(name)
    //         new_database = Database.create(name, self.get_work_dir())
    //         self.databases.append(name)

    //     def drop_database(self, name):
    //         self.assert_db_exists(name)
    //         self.assert_db_not_connected(name)
    //         database = Database.create(name, self.get_work_dir())
    //         Database.destroy(database)
    //         self.databases.remove(name)

    //     #########################################################

    //     def connect(self, name):
    //         self.assert_db_not_connected(name)
    //         database = Database.create(name, self.get_work_dir(),
    //         connect=True) self.connected_dbs[name] = database return database

    //     def get_database(self, name):
    //         self.assert_db_connected(name)
    //         return self.connected_dbs[name]

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

    //     def disconnect_all_dbs(self):
    //         connected_dbs_names = self.list_connected_database()
    //         for dbname in connected_dbs_names:
    //             self.disconnect(dbname)

    //     #########################################################

    //     def close(self):
    //         self.disconnect_all_dbs()

    // #############################################################
    // #                                                           #
    // #############################################################
}  // namespace SQLEngine::DBLib::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
