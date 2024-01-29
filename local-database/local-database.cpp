
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

    using IQuery = Interface::IQuery;

    //////////////////////////////////////////////////////////////////////

    class LocalJSONDatabase : public Interface::IConnectDataBase
    {
       public:
        ~LocalJSONDatabase()
        {
            Disconnect();
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
            AssertConnected();
            Disconnect(m_path);
        }
        void Disconnect(const std::string& workdir) override
        {
            AssertConnected();
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
            auto writer = CreateDBLocalJSONWriter(path);
            writer->Write(*m_database);
        }

       public:
        auto Copy() const -> UDataBase override
        {
            AssertConnected();
            return (m_database->Copy());
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

       public:
        void Execute(const Interface::IQuery& query) override
        {
            AssertConnected();
            return m_database->Execute(query);
        }

        //////////////////////////////////////////////////////////////////

       protected:
        void AssertConnected() const
        {
            Utility::Assert(m_database != nullptr,
                            "LocalJSONDatabase::AssertConnected()");
        }
        void AssertDisconnected() const
        {
            Utility::Assert(m_database == nullptr,
                            "LocalJSONDatabase::AssertDisconnected()");
        }

       public:
        Interface::UDataBase m_database;
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // auto Init(const std::string& workdir) -> Interface::UConnectDataBase
    // {
    // }
    // auto Connect(const std::string& workdir) -> Interface::UConnectDataBase
    // {
    // }
    // void Disconnect(Interface::UConnectDataBase db)
    // {
    // }
    // void Disconnect(Interface::UConnectDataBase db, const std::string&
    // workdir)
    // {
    // }
    // void Drop(Interface::UConnectDataBase db)
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
