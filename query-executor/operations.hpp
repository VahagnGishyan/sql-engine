
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryExecutor
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IOperation;

    using UOperation = std::unique_ptr<IOperation>;

    class IOperation
    {
       public:
        virtual ~IOperation() = default;

       public:
        virtual auto Execute(const Interface::ITable& table) const
            -> Interface::UTable = 0;
        // for debug
        virtual auto ToString() const -> const std::string = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT CreateOpInsertInto(Interface::URowList row)
        -> UOperation;

    // class InsertIntoSettings
    // {
    //    public:
    //     virtual ~InsertIntoSettings() = default;

    //    public:
    // };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
