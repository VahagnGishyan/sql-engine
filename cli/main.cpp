
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "logging/logging.hpp"
// #include "utility/core.hpp"

#include "cli-app-manager.hpp"
#include "local-database/local-database.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::CLI
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    int Main(const int count, char **values)
    {
        IOManager io;
        Interface::UConnectDataBase db = LocalDataBase::Create();

        while (true)
        {
            auto &&input = io.ReadUserInput("your-command: ");
            if (io.IsEnd(input) == true)
            {
                break;
            }

            auto command = ParseInput(input);
            auto&& result = command->ExecuteFor(*db);
            io.PrintMessage(result);
        };

        return 0;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

int main(const int argc, char **argv)
{
    int returnKey = 1;
    try
    {
        SQLEngine::Logging::Init();
        SQLEngine::Logging::Info("Program cli.");
        SQLEngine::Logging::Signal("Start Main().");
        SQLEngine::Logging::Signal(
            fmt::format("log-dir: {}", SQLEngine::Logging::GetLogPath()));
        returnKey = SQLEngine::CLI::Main(argc, argv);
        SQLEngine::Logging::Signal("Close Main().");
    }
    catch (std::exception &err)
    {
        fmt::println("Catch exception, type is std::exception, message is {}",
                     err.what());
    }
    catch (...)
    {
        fmt::println("Unknown type exception was not handled");
    }
    return (returnKey);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
