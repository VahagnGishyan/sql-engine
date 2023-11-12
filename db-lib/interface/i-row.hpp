
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-object.hpp"
#include "i-row-component.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IRow : public IDBObject
    {
    };

    using URow    = std::unique_ptr<IRow>;
    using ShRow   = std::shared_ptr<IRow>;
    using RowList = std::vector<URow>;

    //////////////////////////////////////////////////////////////////////

    template <typename T, typename... Types>
    PROJECT_SHARED_EXPORT auto MakeRow(Types&&... args) -> URow
    {
        static_assert(std::is_base_of<IRow, T>());
        return std::make_unique<T>(args...);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
