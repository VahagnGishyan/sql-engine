
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-filestream.hpp"
#include "i-db-manager-component.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDBManagerInit : public IDBManagerComponent
    {
       public:
        virtual ~IDBManagerInit() = default;

       public:
        virtual auto GetWorkDir() const -> const std::string = 0;
        virtual auto GetName() const -> const std::string    = 0;
        virtual auto GetFileStream() const -> ShFileStream   = 0;
    };

    using UDBManagerInit  = std::unique_ptr<IDBManagerInit>;
    using ShDBManagerInfo = std::shared_ptr<IDBManagerInit>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
