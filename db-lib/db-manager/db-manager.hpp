
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <optional>

#include "i-db-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DBManagerInit : public IDBManagerInit
    {
       public:
        auto GetWorkDir() const -> const std::string override;
        auto GetName() const -> const std::string override;
        auto GetFileStream() const -> ShFileStream override;

       public:
        virtual void SetWorkDir(const std::string&);
        virtual void SetName(const std::string&);
        virtual void SetFileStream(ShFileStream);

       public:
        static auto Create(const std::string& name,
                           ShFileStream filestream = nullptr) -> UDBManagerInit;

       protected:
        std::string m_workdir;
        std::string m_name;
        ShFileStream m_filestream;
    };

    //////////////////////////////////////////////////////////////////////

    class DBManagerInfo : public IDBManagerInfo
    {
       public:
        virtual auto GetWorkDir() const -> const std::string override;
        virtual auto GetName() const -> const std::string override;
    };

    //////////////////////////////////////////////////////////////////////

    class DBManager : public IDBManager
    {
       public:
        auto GetWorkDir() const -> const std::string override;

       public:
        auto DatabaseExists(const IDataBaseID& dbid) const -> bool override;
        auto DatabaseConnected(const IDataBaseID& dbid) const -> bool override;

       public:
        auto ListDatabase() const -> UDataBaseIDList override;
        auto ListConnectedDatabase() const -> UDataBaseIDList override;

       public:
        void AssertDBExists(const IDataBaseID& dbid) const override;
        void AssertDBNotExists(const IDataBaseID& dbid) const override;
        void AssertDBConnected(const IDataBaseID& dbid) const override;
        void AssertDBNotConnected(const IDataBaseID& dbid) const override;

       public:
        void Connect(const IDBManagerInit& data) override;
        void Disconnect() override;

       public:
        auto CreateDatabase(const IDataBaseID& dbid) -> UDataBase override;
        auto GetDatabase(const IDataBaseID& dbid) -> IDataBase& override;
        void DropDatabase(const IDataBaseID& dbid) override;

       protected:
        virtual auto GetDatabaseOptional(const IDataBaseID& dbid) const
            -> std::optional<IDataBase&>;

       protected:
        UFileStream m_fstream;
        UDBManagerInfo m_info;
        DataBaseList m_databases;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
