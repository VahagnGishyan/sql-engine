
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "db-filestream.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////

    void FileStream::SaveTable(const ITable& table) const
    {
        NotImplYet("db-filestream::FileStream::SaveTable");
    }
    void FileStream::LoadTable(ITable& table) const
    {
        NotImplYet("db-filestream::FileStream::LoadTable");
    }

    //////////////////////////////////////////////////////////////////////

    void FileStream::SaveDataBase(const IDataBase& database) const
    {
        NotImplYet("db-filestream::FileStream::SaveDataBase");
    }
    void FileStream::LoadDataBase(IDataBase& database) const
    {
        NotImplYet("db-filestream::FileStream::LoadDataBase");
    }

    //////////////////////////////////////////////////////////////////////

    void FileStream::SaveDBManager(const IDBManagerData& dbmanager) const
    {
        NotImplYet("db-filestream::FileStream::SaveDBManager");
    }
    void FileStream::LoadDBManager(IDBManagerData& dbmanager) const
    {
        NotImplYet("db-filestream::FileStream::LoadDBManager");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto FileStream::Create() -> UFileStream
    {
        return UFileStream{new FileStream};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////