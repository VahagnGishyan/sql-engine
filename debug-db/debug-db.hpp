
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-database.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DebugDB
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT ColumnToStrList(const Interface::IColumn& column)
        -> std::vector<std::string>;
    auto PROJECT_SHARED_EXPORT TableToStrList(const Interface::ITable& column)
        -> std::vector<std::string>;
    auto PROJECT_SHARED_EXPORT DataBaseToStrList(const Interface::IDataBase& column)
        -> std::vector<std::string>;

    void PROJECT_SHARED_EXPORT PrintColumn(const Interface::IColumn&);
    void PROJECT_SHARED_EXPORT PrintTable(const Interface::ITable&);
    void PROJECT_SHARED_EXPORT PrintDataBase(const Interface::IDataBase&);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void PROJECT_SHARED_EXPORT CheckColumn(const Interface::IColumn& actual,
                                           const Interface::IColumn& shouldBe);
    void PROJECT_SHARED_EXPORT CheckTables(const Interface::ITable& actual,
                                           const Interface::ITable& shouldBe);
    void PROJECT_SHARED_EXPORT
    CheckDatabase(const Interface::IDataBase& actual,
                  const Interface::IDataBase& shouldBe);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DebugDB

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////