
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-component.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IColumnComponent
    {
       public:
        virtual ~IColumnComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////

    class IColumnElement : public IColumnComponent
    {
    };

    //////////////////////////////////////////////////////////////////////

    class IColumnID : public IColumnComponent
    {
    };

    //////////////////////////////////////////////////////////////////////

    class IColumnInfo : public IColumnComponent, public IDBComponentInfo
    {
    };

    //////////////////////////////////////////////////////////////////////

    class IColumn : public IDBComponent
    {
    };

    using UColumn    = std::unique_ptr<IColumn>;
    using ShColumn   = std::shared_ptr<IColumn>;
    using ColumnList = std::vector<UColumn>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////