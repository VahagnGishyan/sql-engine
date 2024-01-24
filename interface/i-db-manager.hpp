
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-database.hpp"
#include "interface/i-db-manager-info.hpp"
#include "interface/i-db-manager-init.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // class PROJECT_SHARED_EXPORT IDBManager : public IDBObject
    // {
    //    public:
    //     virtual auto GetInfo() const -> const WDBObjectInfo = 0;

    //    public:
    //     virtual void Connect(const Interface::IDBManagerInit& data) = 0;
    //     virtual void Disconnect()                                   = 0;

    //    public:
    //     virtual auto DatabaseExists(const IDataBaseID& dbid) const -> bool = 0;

    //    public:
    //     virtual auto ListDatabase() const -> UDataBaseIDList          = 0;
    //     virtual auto ListConnectedDatabase() const -> UDataBaseIDList = 0;

    //    public:
    //     virtual void AssertDBExists(const IDataBaseID& dbid) const       = 0;
    //     virtual void AssertDBNotExists(const IDataBaseID& dbid) const    = 0;
    //     virtual void AssertDBConnected(const IDataBaseID& dbid) const    = 0;
    //     virtual void AssertDBNotConnected(const IDataBaseID& dbid) const = 0;

    //    public:
    //     virtual auto CreateDatabase(const IDataBaseID& dbid) -> WDataBase = 0;
    //     virtual void ConnectDatabase(const IDataBaseID& data)             = 0;
    //     virtual auto DatabaseConnected(const IDataBaseID& dbid) const
    //         -> bool                                                    = 0;
    //     virtual auto GetDatabase(const IDataBaseID& dbid) -> WDataBase = 0;
    //     virtual void DropDatabase(const IDataBaseID& dbid)             = 0;
    //     virtual void DisconnectDatabase(const IDataBaseID& dbid)       = 0;
    // };

    // using UDBManagerData = std::unique_ptr<IDBManager>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
