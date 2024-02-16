
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////

#include "cli-app-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::CLI
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace CreateOp
    {
        auto Help(std::vector<std::string> data) -> UOperation;
        auto WorkDir() -> UOperation;

        auto InitAt(const std::string& path) -> UOperation;
        auto ConnectTo(const std::string& path) -> UOperation;
        auto Disconnect() -> UOperation;
        auto DisconnectPath(const std::string& path) -> UOperation;
        auto SaveAt(const std::string& path) -> UOperation;
        auto Drop() -> UOperation;

        auto Rename(const std::string& newname) -> UOperation;
        auto AddTable(const std::string& tableName) -> UOperation;
        auto RemoveTable(const std::string& tableName) -> UOperation;
        auto RenameTable(const std::string& tableName,
                         const std::string& newname) -> UOperation;
        auto ListTables() -> UOperation;

        auto TableAddColumn(const std::string& tableName,
                            const std::string& columnName,
                            const std::string& columnType) -> UOperation;
        auto TableDropColumn(const std::string& tableName,
                             const std::string& columnName) -> UOperation;
        auto TableRenameColumn(const std::string& tableName,
                               const std::string& columnName,
                               const std::string& newColumnName) -> UOperation;
        auto TableListColumns(const std::string& tableName) -> UOperation;

        auto ExecuteJSON(const std::string& path) -> UOperation;

        auto PrintDataBase() -> UOperation;
        auto PrintTable(const std::string& tableName) -> UOperation;
        auto PrintColumn(const std::string& tableName,
                         const std::string& columnName) -> UOperation;
    }  // namespace CreateOp

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class WorkDir : public Operation
    {
       public:
        auto ExecuteFor(Interface::UConnectDataBase& db) const
            -> std::vector<std::string>
        {
            std::vector<std::string> result;
            // result.push_back(db.)
        }
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
