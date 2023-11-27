
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-database.hpp"
#include "i-db-object.hpp"
#include "i-query.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IQueryExecutor : public IDBObject
    {
       public:
        void Execute(IDataBase& database, const IQuery& query);
    };

    using UQueryExecutor    = std::unique_ptr<IQueryExecutor>;
    using ShQueryExecutor   = std::shared_ptr<IQueryExecutor>;
    using QueryExecutorList = std::vector<ShQueryExecutor>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////