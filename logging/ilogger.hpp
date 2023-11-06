
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "log-core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    class ILogger
    {
       public:
        virtual ~ILogger() = default;

       public:
        virtual void Init() = 0;
        // virtual void Init(const std::string &logdir)   = 0;
        virtual auto GetLogPath() -> const std::string = 0;

       public:
        virtual void Message(const std::string &message)                   = 0;
        virtual void Info(const std::string &message)                      = 0;
        virtual void Signal(const std::string &message)                    = 0;
        virtual void Warning(const std::string &message)                   = 0;
        virtual void Debug(const std::string &message)                     = 0;
        virtual void Error(const std::string &message, const bool dothrow) = 0;

       public:
        virtual auto GetMode() const -> const Mode = 0;
        virtual void SetMode(const Mode &)         = 0;
    };

    using ULogger = std::unique_ptr<ILogger>;
}  // namespace SQLEngine::Logging

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
