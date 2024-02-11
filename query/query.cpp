
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include "condition.hpp"
#include "database/database.hpp"
#include "executors.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Query
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using IQuery         = Interface::IQuery;
    using UQuery         = Interface::UQuery;
    using UQueryExecutor = Interface::UQueryExecutor;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Query : public IQuery
    {
       public:
        Query(const std::string& tablename,
              Interface::UQueryExecutor executor) :
            m_tablename{tablename}, m_executor{std::move(executor)}
        {
        }

       public:
        auto GetTableName() const -> const std::string override
        {
            return m_tablename;
        }
        auto GetQueryExecutor() const -> UQueryExecutor override
        {
            return m_executor->Copy();
        }

       protected:
        std::string m_tablename;
        UQueryExecutor m_executor;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateQuery(const std::string& tablename,
                     Interface::UQueryExecutor executor) -> Interface::UQuery
    {
        return std::make_unique<Query>(tablename, std::move(executor));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Query

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
