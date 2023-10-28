
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "logging.hpp"
#include "easy-log.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// def PrintInfo(message):
//     print(GREEN + message + RESET)

// def PrintSignal(message):
//     print(GREEN + message + RESET)

// def PrintWarning(message):
//     print(YELLOW + message + RESET)

// def PrintDebug(message):
//     print(BLUE + message + RESET)

// def PrintError(message):
//     print(RED + message + RESET)

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    static auto GetLogger() -> ILogger &
    {
        static ULogger logger = std::make_unique<EasyLog>();
        return *(logger);
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

    void SetLogDir(const std::string &path)
    {
        auto &&logger = GetLogger();
        logger.SetLogDir(path);
    }

    auto GetLogDir() -> const std::string
    {
        auto &&logger = GetLogger();
        return logger.GetLogDir();
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

    void Error(const std::string &message, const bool dothrow = false)
    {
        auto &&logger = GetLogger();
        logger.Error(message, false);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
