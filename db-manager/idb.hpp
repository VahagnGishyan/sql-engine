
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

namespace SQLEngine::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBComponent
    {
       public:
        virtual ~IDBComponent() = default;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ITable : public IDBComponent
    {
    };

    using UTable = std::unique_ptr<ITable>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDataBaseID : public IDBComponent
    {
       public:
        virtual auto GetDataBaseName() const -> const std::string = 0;
    };

    using UDataBaseID     = std::unique_ptr<IDataBaseID>;
    using DataBaseIDList  = std::vector<UDataBaseID>;
    using UDataBaseIDList = std::unique_ptr<DataBaseIDList>;

    //////////////////////////////////////////////////////////////////////

    class IDataBase : public IDBComponent
    {
    };

    using UDataBase = std::unique_ptr<IDataBase>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBManagerInit : public IDBComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string = 0;
    };

    //////////////////////////////////////////////////////////////////////

    class IDBManager : public IDBComponent
    {
       public:
        virtual auto GetWorkDir() const -> const std::string = 0;

       public:
        virtual auto DatabaseExists() const -> bool    = 0;
        virtual auto DatabaseConnected() const -> bool = 0;

       public:
        virtual auto ListDatabase() const -> UDataBaseIDList          = 0;
        virtual auto ListConnectedDatabase() const -> UDataBaseIDList = 0;

       public:
        virtual void AssertDBExists() const       = 0;
        virtual void AssertDBNotExists() const    = 0;
        virtual void AssertDBConnected() const    = 0;
        virtual void AssertDBNotConnected() const = 0;

       public:
        virtual void Connect(const IDBManagerInit& data) = 0;
        virtual void Disconnect()                        = 0;

       public:
        virtual auto CreateDatabase() -> UDataBase                      = 0;
        virtual auto GetDatabase(const IDataBaseID& dbid) -> IDataBase& = 0;
        virtual void DropDatabase(const IDataBaseID& dbid);
    };

    using UDBManager = std::unique_ptr<IDBManager>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
