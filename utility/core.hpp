
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Utility
{
    PROJECT_SHARED_EXPORT auto GetEnvironmentValue(const std::string& name)
        -> const std::string;

    PROJECT_SHARED_EXPORT
    auto GetDefaultDataPath() -> const std::string;

    PROJECT_SHARED_EXPORT
    void Assert(const bool condition, const std::string& info);
}  // namespace SQLEngine::Utility

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
