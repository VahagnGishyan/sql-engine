
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-component.hpp"
#include "i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDataBaseComponent
    {
       public:
        virtual ~IDataBaseComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////

    class IDataBaseElement : public IDataBaseComponent
    {
    };

    //////////////////////////////////////////////////////////////////////

    class IDataBaseID : public IDBComponent
    {
       public:
        virtual auto GetName() const -> const std::string = 0;
    };
    using DataBaseIDList  = std::vector<IDataBaseID>;
    using UDataBaseIDList = std::unique_ptr<DataBaseIDList>;

    //////////////////////////////////////////////////////////////////////

    class IDataBaseInfo : public IDataBaseComponent, public IDBComponentInfo
    {
    };

    //////////////////////////////////////////////////////////////////////

    class IDataBaseInit : public IDataBaseComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string           = 0;
        virtual auto GetName() const -> const std::string              = 0;
        virtual auto GetTablesWorkDirPath() const -> const std::string = 0;
        // virtual auto GetTablesWorkDirName() const -> const std::string = 0;
        // virtual auto GetFileStream() const -> const ShFile
        // virtual auto GetTablePath(const ITableID& init) const -> const
        // std::string = 0;
    };

    //////////////////////////////////////////////////////////////////////

    class IDataBase : public IDBComponent
    {
       public:
        virtual auto GetDataBaseID() const -> const IDataBaseID& = 0;
        virtual auto GetInfo() const -> const ShDBComponentInfo  = 0;

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

    using UDataBase = std::unique_ptr<IDataBase>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
