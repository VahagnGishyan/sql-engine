
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

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

    class IDataBaseID : public IDBObject
    {
       public:
        virtual auto GetName() const -> const std::string = 0;
    };
    using UDataBaseID     = std::unique_ptr<IDataBaseID>;
    using ShDataBaseID    = std::shared_ptr<IDataBaseID>;
    using DataBaseIDList  = std::vector<ShDataBaseID>;
    using UDataBaseIDList = std::unique_ptr<DataBaseIDList>;

    //////////////////////////////////////////////////////////////////////

    class IDataBaseInfo : public IDataBaseComponent, public IDBObjectInfo
    {
    };
    using UDataBaseInfo     = std::unique_ptr<IDataBaseInfo>;
    using ShDataBaseInfo    = std::shared_ptr<IDataBaseInfo>;
    using DataBaseInfoList  = std::vector<ShDataBaseInfo>;
    using UDataBaseInfoList = std::unique_ptr<DataBaseInfoList>;

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
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
