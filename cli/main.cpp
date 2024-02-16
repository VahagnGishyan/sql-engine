
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

    auto GetDBName(const Interface::IConnectDataBase &db) -> std::string
    {
        std::string name = "cli";
        if (db.IsConnected())
        {
            name = db.GetName();
        }

        return name;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    int Main(const int count, char **values)
    {
        IOManager io;
        Interface::UConnectDataBase db = LocalDataBase::Create();

        while (true)
        {
            try
            {
                auto &&input = io.ReadUserInput(GetDBName(*db));
                if (io.IsEnd(input) == true)
                {
                    break;
                }

                auto command  = ParseInput(input);
                auto &&result = command->ExecuteFor(*db);
                io.PrintMessage(result);
            }
            catch (std::exception &err)
            {
                io.PrintError(
                    fmt::format("Catch exception, message is {}", err.what()));
            }
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
        returnKey = SQLEngine::CLI::Main(argc, argv);
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

/*
save-at
*/