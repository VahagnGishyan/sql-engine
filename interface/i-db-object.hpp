
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDBObjectInfo
    {
       public:
        virtual ~IDBObjectInfo() = default;

       public:
        virtual auto GetName() -> const std::string = 0;
    };

    using UDBObjectInfo  = std::unique_ptr<IDBObjectInfo>;
    using ShDBObjectInfo = std::shared_ptr<IDBObjectInfo>;
    using WDBObjectInfo  = std::weak_ptr<IDBObjectInfo>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDBObject
    {
       public:
        virtual ~IDBObject() = default;

       public:
        // auto GetWorkDir() const -> const std::string override;
        // virtual auto GetInfo() const -> const UDBObjectInfo = 0;
    };

    //////////////////////////////////////////////////////////////////////

    class IRowOrientedTable;
    class IColumn;
    class ITable;
    class IDataBase;
    class IDBManager;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IColumnComponent
    {
       public:
        virtual ~IColumnComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT ITableComponent
    {
       public:
        virtual ~ITableComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDataBaseComponent
    {
       public:
        virtual ~IDataBaseComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // temp
    PROJECT_SHARED_EXPORT
    void NotImplYet(const std::string& info);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
