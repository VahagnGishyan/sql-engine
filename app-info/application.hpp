
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Application
{
    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Info
    {
       public:
        virtual ~Info() = default;

       public:
        virtual auto GetName() const -> const std::string & = 0;
        virtual auto GetDefaultAppData(
            const bool createIfNotExists = true) const -> const std::string = 0;
        virtual auto GetVersion() const -> const std::string              & = 0;
    };

    using UInfo = std::unique_ptr<Info>;

    //////////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT GetInfo() -> const Info &;

    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Application

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
