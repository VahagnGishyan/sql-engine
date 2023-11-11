
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-database.hpp"
#include "i-db-component.hpp"
#include "i-db-filestream.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBManagerInitializer : public IDBComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string     = 0;
        virtual auto GetFileStream() const -> const IFileStream& = 0;
    };

    //////////////////////////////////////////////////////////////////////

    class IDBManagerInfo : public IDBComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string = 0;
        virtual auto GetName() const -> const std::string    = 0;
    };
    using UDBManagerInfo = std::unique_ptr<IDBManagerInfo>;

    //////////////////////////////////////////////////////////////////////

    class IDBManager : public IDBComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string           = 0;
        virtual auto GetDBManagerInfo() const -> const IDBManagerInfo& = 0;

       public:
        virtual auto DatabaseExists(const IDataBaseID& dbid) const -> bool = 0;
        virtual auto DatabaseConnected(const IDataBaseID& dbid) const
            -> bool = 0;

       public:
        virtual auto ListDatabase() const -> UDataBaseIDList          = 0;
        virtual auto ListConnectedDatabase() const -> UDataBaseIDList = 0;

       public:
        virtual void AssertDBExists(const IDataBaseID& dbid) const       = 0;
        virtual void AssertDBNotExists(const IDataBaseID& dbid) const    = 0;
        virtual void AssertDBConnected(const IDataBaseID& dbid) const    = 0;
        virtual void AssertDBNotConnected(const IDataBaseID& dbid) const = 0;

       public:
        virtual void Connect(const IDBManagerInitializer& data) = 0;
        virtual void Disconnect()                               = 0;

       public:
        virtual auto CreateDatabase(const IDataBaseID& dbid) -> UDataBase = 0;
        virtual auto GetDatabase(const IDataBaseID& dbid) -> IDataBase&   = 0;
        virtual void DropDatabase(const IDataBaseID& dbid)                = 0;
    };

    using UDBManager = std::unique_ptr<IDBManager>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
