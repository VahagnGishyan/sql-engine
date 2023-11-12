
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-database-component.hpp"
#include "i-db-object.hpp"
#include "i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDataBase : public IDBObject
    {
       public:
        virtual auto GetDataBaseID() const -> const IDataBaseID& = 0;
        virtual auto GetInfo() const -> const ShDataBaseInfo  = 0;
        virtual auto GetID() const -> const ShDataBaseID  = 0;

       public:
        virtual auto IsConnected() const -> bool           = 0;
        virtual void SetConnection(const bool isconnected) = 0;
        virtual void AssertConnected() const               = 0;
        virtual void AssertNotConnected() const            = 0;

       public:
        virtual void Connect(const IDataBaseInit& init) = 0;
        virtual void Disconnect()                       = 0;

       public:
        virtual auto ListTables() const -> const ShTableIDList         = 0;
        virtual auto IsTableExists(const ITableID& tbid) const -> bool = 0;
        virtual void AssertConnected(const ITableID& tbid) const       = 0;
        virtual void AssertTableNotExists(const ITableID& tbid) const  = 0;

       public:
        virtual auto CreateTable(const ITableInit& init) -> ShTable        = 0;
        virtual void DropTable(const ITableID& init)                       = 0;
        virtual auto GetTable(const ITableID& init) -> ShTable             = 0;
        virtual auto GetTable(const ITableID& init) const -> const ShTable = 0;
    };

    using UDataBase    = std::unique_ptr<IDataBase>;
    using ShDataBase   = std::shared_ptr<IDataBase>;
    using DataBaseList = std::vector<ShDataBase>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
