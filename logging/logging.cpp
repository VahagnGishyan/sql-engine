
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "logging.hpp"

#include "ilogger.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    static auto GetLogger() -> ILogger &
    {
        static ULogger logger = MakeUniqueLogger();
        return *(logger);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Init()
    // void Init(const std::string &logdir)
    {
        auto &&logger = GetLogger();
        logger.Init(/*logdir*/);
    }

    //////////////////////////////////////////////////////////////////////

    auto GetLogPath() -> const std::string
    {
        auto &&logger = GetLogger();
        return logger.GetLogPath();
    }

    //////////////////////////////////////////////////////////////////////

    void EnableBuffering(const bool order)
    {
        auto &&logger = GetLogger();
        return logger.EnableBuffering(order);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void SetMode(const Mode &mod)
    {
        auto &&logger = GetLogger();
        logger.SetMode(mod);
    }

    auto GetMode() -> const Mode
    {
        auto &&logger = GetLogger();
        return logger.GetMode();
    }

    //////////////////////////////////////////////////////////////////////

    void Message(const std::string &message)
    {
        auto &&logger = GetLogger();
        logger.Message(message);
    }

    void Info(const std::string &message)
    {
        auto &&logger = GetLogger();
        logger.Info(message);
    }

    void Signal(const std::string &message)
    {
        auto &&logger = GetLogger();
        logger.Signal(message);
    }

    void Warning(const std::string &message)
    {
        auto &&logger = GetLogger();
        logger.Warning(message);
    }

    void Debug(const std::string &message)
    {
        auto &&logger = GetLogger();
        logger.Debug(message);
    }

    void Error(const std::string &message, const bool dothrow)
    {
        auto &&logger = GetLogger();
        logger.Error(message, dothrow);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Logging

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
