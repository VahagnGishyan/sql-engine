
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-database-component.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDataBaseInfo : public IDataBaseComponent, public IDBObjectInfo
    {
    };
    using UDataBaseInfo     = std::unique_ptr<IDataBaseInfo>;
    using ShDataBaseInfo    = std::shared_ptr<IDataBaseInfo>;
    using DataBaseInfoList  = std::vector<ShDataBaseInfo>;
    using UDataBaseInfoList = std::unique_ptr<DataBaseInfoList>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
