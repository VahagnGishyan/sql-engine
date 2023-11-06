
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "logging/logging.hpp"
#include "utility/core.hpp"
#include "logging/logging.hpp"

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
        SQLEngine::Logging::Message("First log");
        SQLEngine::Logging::Info("First log");
        SQLEngine::Logging::Signal("First log");
        SQLEngine::Logging::Debug("First log");
        SQLEngine::Logging::Warning("First log");
        SQLEngine::Logging::Error("First log");
        return 0;
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
        std::cout << "Start Main()" << std::endl;
        returnKey = SQLEngine::Observer::Main(argc, argv);
        std::cout << "Close Main()" << std::endl;
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
