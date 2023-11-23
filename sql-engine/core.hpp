
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>

#include "database.hpp"
#include "engine.hpp"
#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Init(UEngine engine);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool DatabaseExists(const std::string& name);
    auto ListDatabases() -> DataBaseNameList;
    auto ListConnectedDatabases() -> DataBaseNameList;

    auto CreateDatabase(const std::string& name) -> WDataBase;
    void DropDatabase(const std::string& name);

    auto ConnectDatabase(const std::string& name) -> WDataBase;
    void DisconnectDatabase(const std::string& name);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // virtual auto AlterTableAdd(const ITableID& tbid, const IColumnID, const DataType) -> ShTable    = 0;
    // virtual auto AlterTableDrop(const ITableID& tbid, const IColumnID) -> ShTable                   = 0;
    // virtual auto AlterTableRename(const ITableID& tbid, const IColumnID, const DataType) -> ShTable = 0;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
