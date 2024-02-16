
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <optional>

#include "interface/i-database.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::LocalDataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT CreateColumn(const std::string& name,
                                            const Interface::DynamicType& type)
        -> Interface::UColumn;
    auto PROJECT_SHARED_EXPORT CreateTable(const std::string& newname)
        -> Interface::UTable;

    auto PROJECT_SHARED_EXPORT Init(const std::string& newdbpath)
        -> Interface::UConnectDataBase;
    auto PROJECT_SHARED_EXPORT Connect(const std::string& dbpath)
        -> Interface::UConnectDataBase;
    auto PROJECT_SHARED_EXPORT Create() -> Interface::UConnectDataBase;
    void PROJECT_SHARED_EXPORT SaveAt(Interface::IConnectDataBase& db,
                                      const std::string& dbpath);
    void PROJECT_SHARED_EXPORT Disconnect(Interface::IConnectDataBase& db);
    void PROJECT_SHARED_EXPORT Disconnect(Interface::IConnectDataBase& db,
                                          const std::string& newdbpath);
    void PROJECT_SHARED_EXPORT Drop(Interface::IConnectDataBase& db);
    void PROJECT_SHARED_EXPORT Drop(const std::string& newdbpath);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
