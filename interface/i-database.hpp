
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-object.hpp"
#include "i-query.hpp"
#include "i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDataBase;

    using UDataBase    = std::unique_ptr<IDataBase>;
    using ShDataBase   = std::shared_ptr<IDataBase>;
    using WDataBase    = std::weak_ptr<IDataBase>;
    using DataBaseList = std::vector<ShDataBase>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDataBase : public IDBObject
    {
       public:
        virtual auto Copy(const std::string& dbname) const -> UDataBase = 0;
        virtual auto Copy() const -> UDataBase                          = 0;

       public:
        virtual auto GetName() const -> const std::string& = 0;
        virtual void SetName(const std::string& name)      = 0;

       public:
        virtual void AddTable(UTable table)                  = 0;
        virtual void RemoveTable(const std::string& tbname)  = 0;
        virtual void RenameTable(const std::string& oldname,
                                 const std::string& newname) = 0;

       public:
        virtual auto TablesCount() const -> const int                       = 0;
        virtual auto ListTables() const -> UTableNameList                   = 0;
        virtual auto IsTableExists(const std::string& tbname) const -> bool = 0;

       public:
        virtual auto GetTable(const std::string& tbname) -> ITable& = 0;
        virtual auto GetTable(const std::string& tbname) const
            -> const ITable& = 0;

       public:
        virtual void Execute(const IQuery& query) = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
