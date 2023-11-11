
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

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBComponentInfo
    {
       public:
        virtual ~IDBComponentInfo() = default;

       public:
        virtual auto GetName() -> const std::string = 0;
    };

    using UDBComponentInfo  = std::unique_ptr<IDBComponentInfo>;
    using ShDBComponentInfo = std::shared_ptr<IDBComponentInfo>;

    //////////////////////////////////////////////////////////////////////

    class IDBComponent
    {
       public:
        virtual ~IDBComponent() = default;

       public:
        virtual auto GetInfo() const -> const ShDBComponentInfo = 0;
    };

    //////////////////////////////////////////////////////////////////////

    class IRow;
    class IColumn;
    class ITable;
    class IDataBase;
    class IDBManager;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////