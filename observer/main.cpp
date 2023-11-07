
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/format.h>

#include <iostream>

#include "db-manager/database.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Observer
{
    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////

    void CheckCore()
    {
        std::cout << "Path is    " << Utility::GetEnvironmentValue("PATH")
                  << std::endl;
        std::cout << "WorkDir is " << Utility::GetDefaultDataPath()
                  << std::endl;
    }

    int Main(const int count, char **values)
    {
        DBManager::DataBase db{};
        db.DoSomething();
        return (0);
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Observer

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(const int argc, char **argv)
{
    int returnKey = 1;
    try
    {
        SQLEngine::Logging::Info("Program observer.");
        SQLEngine::Logging::Signal("Start Main().");
        SQLEngine::Logging::Signal(
            fmt::format("log-dir: {}", SQLEngine::Logging::GetLogPath()));
        returnKey = SQLEngine::Observer::Main(argc, argv);
        SQLEngine::Logging::Signal("Close Main().");
    }
    catch (std::exception &err)
    {
        std::cout
            << std::string(
                   "Catch exception, type is std::exception, message is ") +
                   err.what()
            << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown type exception was not handled" << std::endl;
    }
    return (returnKey);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
