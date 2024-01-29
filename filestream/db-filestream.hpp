
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-database.hpp"
#include "interface/i-db-filestream.hpp"
#include "interface/i-db-manager.hpp"
#include "interface/i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::LocalDataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class FileStream : public Interface::IFileStream
    {
        //    private:
        //     FileStream() = default;

        //    public:
        //     void SaveTable(const ITable& table) const override;
        //     void LoadTable(ITable& table) const override;

        //    public:
        //     void SaveDataBase(const IDataBase& database) const override;
        //     void LoadDataBase(IDataBase& database) const override;

        //    public:
        //     void SaveLocalDataBase(const ILocalDataBase& dbmanager) const override;
        //     void LoadLocalDataBase(ILocalDataBase& dbmanager) const override;

        //    public:
        //     static auto Create() -> UFileStream;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
