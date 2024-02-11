
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "local-database.hpp"

#include "database/database.hpp"
#include "db-local-json-stream.hpp"
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

    using ITable         = Interface::ITable;
    using UTable         = Interface::UTable;
    using TableList      = Interface::TableList;
    using UTableNameList = Interface::UTableNameList;

    using IDataBase = Interface::IDataBase;
    using UDataBase = Interface::UDataBase;

    using IQueryExecutor = Interface::IQueryExecutor;

    //////////////////////////////////////////////////////////////////////

    /*
        temp,
        add sql-executor here
    */

    class LocalJSONDatabase : public Interface::IConnectDataBase
    {
       public:
        LocalJSONDatabase() : m_database{}, m_path{}
        {
        }

       protected:
        LocalJSONDatabase(UDataBase db, const std::string& path) :
            m_database{std::move(db)}, m_path{path}
        {
            auto&& dbname = m_database->GetName();
            auto&& fname  = Utility::ExtractFileName(m_path);
            Utility::Assert(dbname == fname,
                            "LocalJSONDatabase::LocalJSONDatabase(db, path)");
        }

       public:
        ~LocalJSONDatabase()
        {
            if (IsConnected())
            {
                Disconnect();
            }
        }

       public:
        void Init(const std::string& newdbpath) override
        {
            AssertDisconnected();
            Utility::MakeDir(newdbpath, Utility::Option::ExistOk{false},
                             Utility::Option::CreateBaseDirectory{true});
            m_database =
                DataBase::CreateDataBase(Utility::ExtractFileName(newdbpath));
            m_path = newdbpath;
        }
        void Connect(const std::string& dbpath) override
        {
            AssertDisconnected();
            auto reader = CreateDBLocalJSONReader(dbpath);
            m_database  = reader->Read();
            m_path      = dbpath;
        }
        void Disconnect() override
        {
            Disconnect(m_path);
        }
        void Disconnect(const std::string& workdir) override
        {
            AssertConnected();
            if (m_path != workdir)
            {
                Utility::RemoveDir(m_path);
            }

            SaveAt(workdir);
            m_database = nullptr;
            m_path     = "";
        }
        void Drop() override
        {
            AssertConnected();
            Utility::RemoveDir(m_path);
            m_database = nullptr;
            m_path     = "";
        }

       protected:
        void SaveAt(const std::string& path) const
        {
            auto writer = CreateDBLocalJSONWriter(Utility::GetBaseDir(path));
            writer->Write(*m_database);
        }

       public:
        auto Copy() const -> Interface::UDataBase override
        {
            return CopyConnectDataBase();
        }
        auto CopyConnectDataBase() const -> Interface::UConnectDataBase override
        {
            Interface::UConnectDataBase database{
                new LocalJSONDatabase{m_database->Copy(), m_path}
            };
            return (database);
        }

        auto Copy(const std::string& newname) const -> UDataBase override
        {
            AssertConnected();
            return (m_database->Copy(newname));
        }

        //////////////////////////////////////////////////////////////////

        auto GetName() const -> const std::string& override
        {
            AssertConnected();
            return (m_database->GetName());
        }
        void SetName(const std::string& name) override
        {
            AssertConnected();
            m_database->SetName(name);
            std::string lastDir = m_path;

            m_path = Utility::GetBaseDir(m_path) + '/' + name;
            SaveAt(m_path);
            Utility::RemoveDir(lastDir);
        }

        //////////////////////////////////////////////////////////////////

       public:
        void AddTable(UTable table) override
        {
            AssertConnected();
            m_database->AddTable(std::move(table));
        }
        void RemoveTable(const std::string& tbname) override
        {
            AssertConnected();
            m_database->RemoveTable(tbname);
        }
        void RenameTable(const std::string& oldtbname,
                         const std::string& newtbname) override
        {
            AssertConnected();
            m_database->RenameTable(oldtbname, newtbname);
        }

        //////////////////////////////////////////////////////////////////

       public:
        auto TablesCount() const -> const int override
        {
            AssertConnected();
            return m_database->TablesCount();
        }

        auto ListTables() const -> UTableNameList override
        {
            AssertConnected();
            return m_database->ListTables();
        }

        auto IsTableExists(const std::string& tbname) const -> bool override
        {
            AssertConnected();
            return m_database->IsTableExists(tbname);
        }
        //////////////////////////////////////////////////////////////////

       public:
        auto GetTable(const std::string& tbname) const -> const ITable& override
        {
            AssertConnected();
            return m_database->GetTable(tbname);
        }
        auto GetTable(const std::string& tbname) -> ITable& override
        {
            AssertConnected();
            return m_database->GetTable(tbname);
        }

        //////////////////////////////////////////////////////////////////

       protected:
        auto IsConnected() const -> bool
        {
            return (m_database != nullptr);
        }
        void AssertConnected() const
        {
            Utility::Assert(IsConnected() == true,
                            "LocalJSONDatabase::AssertConnected()");
        }
        void AssertDisconnected() const
        {
            Utility::Assert(IsConnected() == false,
                            "LocalJSONDatabase::AssertDisconnected()");
        }

       public:
        Interface::UDataBase m_database;
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateColumn(const std::string& name,
                      const Interface::DynamicType& type) -> Interface::UColumn
    {
        return DataBase::CreateColumn(name, type);
    }
    auto CreateTable(const std::string& name) -> Interface::UTable
    {
        return DataBase::CreateTable(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Init(const std::string& newdbpath) -> Interface::UConnectDataBase
    {
        Interface::UConnectDataBase database =
            std::make_unique<LocalJSONDatabase>();
        database->Init(newdbpath);
        // return database;
        return nullptr;
    }
    auto Connect(const std::string& dbpath) -> Interface::UConnectDataBase
    {
        Interface::UConnectDataBase database =
            std::make_unique<LocalJSONDatabase>();
        database->Connect(dbpath);
        return database;
    }
    void Disconnect(Interface::IConnectDataBase& db)
    {
        db.Disconnect();
    }
    void Disconnect(Interface::IConnectDataBase& db,
                    const std::string& newdbpath)
    {
        db.Disconnect(newdbpath);
    }
    void Drop(Interface::IConnectDataBase& db)
    {
        db.Drop();
    }
    void Drop(const std::string& newdbpath)
    {
        Utility::RemoveDir(newdbpath);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
