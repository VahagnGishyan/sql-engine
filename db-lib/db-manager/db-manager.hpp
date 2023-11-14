
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <optional>

#include "db-lib/interface/i-db-manager-comps.hpp"
#include "db-lib/interface/i-db-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Manager : public Interface::IDBManager
    {
        //    public:
        //     auto GetWorkDir() const -> const std::string override;

        //    public:
        //     auto DatabaseExists(const Interface::IDataBaseID& dbid) const
        //         -> bool override;
        //     auto DatabaseConnected(const Interface::IDataBaseID& dbid) const
        //         -> bool override;

        //    public:
        //     auto ListDatabase() const -> Interface::UDataBaseIDList override;
        //     auto ListConnectedDatabase() const
        //         -> Interface::UDataBaseIDList override;

        //    public:
        //     void AssertDBExists(const Interface::IDataBaseID& dbid) const
        //     override; void AssertDBNotExists(
        //         const Interface::IDataBaseID& dbid) const override;
        //     void AssertDBConnected(
        //         const Interface::IDataBaseID& dbid) const override;
        //     void AssertDBNotConnected(
        //         const Interface::IDataBaseID& dbid) const override;

        //    public:
        //     void Connect(const Interface::IDBManagerInit& data) override;
        //     void Disconnect() override;

        //    public:
        //     auto CreateDatabase(const Interface::IDataBaseID& dbid)
        //         -> UDataBase override;
        //     auto GetDatabase(const Interface::IDataBaseID& dbid)
        //         -> IDataBase& override;
        //     void DropDatabase(const Interface::IDataBaseID& dbid) override;

        //    protected:
        //     virtual auto GetDatabaseOptional(const Interface::IDataBaseID&
        //     dbid)
        //         const -> std::optional<Interface::IDataBase&>;

        //    protected:
        //     // Interface::UFileStream m_fstream;
        //     Interface::UDBManagerInfo m_info;
        //     Interface::DataBaseList m_databases;
    };

    PROJECT_SHARED_EXPORT
    void DoSomething();

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
