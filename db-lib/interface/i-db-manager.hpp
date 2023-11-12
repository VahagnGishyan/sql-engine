
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-manager-init.hpp"
#include "i-db-manager-read.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBManager : public IDBManagerRead
    {
       public:
        virtual auto ListDatabase() const -> UDataBaseIDList          = 0;
        virtual auto ListConnectedDatabase() const -> UDataBaseIDList = 0;

       public:
        virtual auto DatabaseExists(const IDataBaseID& dbid) const -> bool = 0;

       public:
        virtual void AssertDBExists(const IDataBaseID& dbid) const       = 0;
        virtual void AssertDBNotExists(const IDataBaseID& dbid) const    = 0;
        virtual void AssertDBConnected(const IDataBaseID& dbid) const    = 0;
        virtual void AssertDBNotConnected(const IDataBaseID& dbid) const = 0;

       public:
        virtual void Connect(const IDBManagerInit& data) = 0;
        virtual void Disconnect()                        = 0;

       public:
        virtual auto CreateDatabase(const IDataBaseID& dbid) -> UDataBase = 0;
        virtual void DropDatabase(const IDataBaseID& dbid)                = 0;
    };

    using UDBManager = std::unique_ptr<IDBManager>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
