
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

#include "log-core.hpp"
#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    PROJECT_SHARED_EXPORT
    void Init();
    // void Init(const std::string &logdir);
    PROJECT_SHARED_EXPORT
    auto GetLogPath() -> const std::string;
    PROJECT_SHARED_EXPORT
    void EnableBuffering(const bool order);

    PROJECT_SHARED_EXPORT
    void Message(const std::string &message);
    PROJECT_SHARED_EXPORT
    void Info(const std::string &message);
    PROJECT_SHARED_EXPORT
    void Signal(const std::string &message);
    PROJECT_SHARED_EXPORT
    void Warning(const std::string &message);
    PROJECT_SHARED_EXPORT
    void Debug(const std::string &message);
    PROJECT_SHARED_EXPORT
    void Error(const std::string &message, const bool dothrow = false);

    PROJECT_SHARED_EXPORT
    auto GetMode() -> const Mode;
    PROJECT_SHARED_EXPORT
    void SetMode(const Mode &);
}  // namespace SQLEngine::Logging

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
