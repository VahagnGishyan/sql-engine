
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>

#include "input-parser.hpp"
#include "logging/logging.hpp"
// #include "utility/core.hpp"

#include <boost/none.hpp>
#include <boost/program_options.hpp>
#include <optional>

#include "cli-app-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace po = boost::program_options;

//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::CLI
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    /*
        help
            prints all commands
        work-dir
            prints work-dir for connected database

        init-at: path
        connect-to: path
        disconnect: optional<path>
        drop
        print: "" | database table | database table column

        rename: db-new-name
        add-table: table-name
        remove-table: table-name
        rename-table: table-name table-name-new
        list-tables

        table-add-column: table-name column-name column-type
        table-drop-column: table-name column-name
        table-rename-column: table-name column-name column-name-new
        table-list-columns: table-name column-name

        execute: path
    */
    //     /*
    //         input-output-manager
    //         parse input and create cl-operations
    //         execute cli-operations
    //     */
    //    ParseInput(count, values);

    void Parse(const int count, char **values)
    {
        assert(count != 1);

        po::options_description desc("Allowed options");
        desc.add_options()("help", "Prints all commands");
        desc.add_options()("work-dir",
                           "Prints work-dir for connected database");

        desc.add_options()("init-at", po::value<std::string>(),
                           "Initialize the database in the path");
        desc.add_options()("connect-to", po::value<std::string>(),
                           "Connects to database existing in path");
        desc.add_options()(
            "disconnect",
            "Disconnects in path where the database already exists");
        desc.add_options()("disconnect-path", po::value<std::string>(),
                           "Disconnect and save at path, args: path");
        desc.add_options()("save-at", po::value<std::string>(),
                           "Saves the database in the path, args: path");
        desc.add_options()("drop", "Drops database");
        desc.add_options()("rename", po::value<std::string>(),
                           "Renames database, args: new-database-name");

        desc.add_options()("add-table", po::value<std::string>(),
                           "Adds new table, args: table-name");
        desc.add_options()("remove-table", po::value<std::string>(),
                           "Removes existing database, args: table-name");
        desc.add_options()("rename-table",
                           po::value<std::vector<std::string>>()->multitoken(),
                           "Renames Table, args: table-name new-table-name");
        desc.add_options()("list-tables", "List tables in database");

        desc.add_options()(
            "table-add-column",
            po::value<std::vector<std::string>>()->multitoken(),
            "Adds column in Tale, args: table-name column-name column-type");
        desc.add_options()("table-drop-column",
                           po::value<std::vector<std::string>>()->multitoken(),
                           "Removes column, args: table-name column-name");
        desc.add_options()(
            "table-rename-column",
            po::value<std::vector<std::string>>()->multitoken(),
            "Renames column, args: table-name column-name column-name-new");
        desc.add_options()("table-list-columns", po::value<std::string>(),
                           "Lists columns in table, args: table-name");

        desc.add_options()("execute-json", po::value<std::string>(),
                           "Executes json-query, args: json-path");

        desc.add_options()("execute", po::value<std::string>(), "path");

        desc.add_options()("print-database", "Prints DataBase");
        desc.add_options()("print-table", po::value<std::string>(),
                           "Prints table, args: table-name");
        desc.add_options()("print-column",
                           po::value<std::vector<std::string>>()->multitoken(),
                           "Prints column, args: table-name column-name");

        po::command_line_parser parser(count, values);
        parser.options(desc);

        po::variables_map vm;
        po::store(parser.run(), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
        }

        if (vm.count("work-dir"))
        {
            std::cout << "operation: "
                      << "work-dir" << std::endl;
        }

        if (vm.count("init-at"))
        {
            const std::string path = vm["init-at"].as<std::string>();
            std::cout << "operation: "
                      << "init-at: path = " << path << std::endl;
        }
        if (vm.count("connect-to"))
        {
            const std::string path = vm["connect-to"].as<std::string>();
            std::cout << "operation: "
                      << "connect-to: path = " << path << std::endl;
        }
        if (vm.count("disconnect"))
        {
            std::cout << "operation: "
                      << "disconnect" << std::endl;
        }
        if (vm.count("disconnect-path"))
        {
            const std::string path = vm["disconnect-path"].as<std::string>();
            std::cout << "operation: "
                      << "disconnect-path: path = " << path << std::endl;
        }
        if (vm.count("save-at"))
        {
            const std::string path = vm["save-at"].as<std::string>();
            std::cout << "operation: "
                      << "save-at: path = " << path << std::endl;
        }
        if (vm.count("drop"))
        {
            std::cout << "operation: "
                      << "drop" << std::endl;
        }
        if (vm.count("rename"))
        {
            const std::string newName = vm["rename"].as<std::string>();
            std::cout << "operation: "
                      << "rename: new-name = " << newName << std::endl;
        }
        if (vm.count("add-table"))
        {
            const std::string name = vm["add-table"].as<std::string>();
            std::cout << "operation: "
                      << "add-table: table-name = " << name << std::endl;
        }
        if (vm.count("remove-table"))
        {
            const std::string name = vm["remove-table"].as<std::string>();
            std::cout << "operation: "
                      << "remove-table: table-name = " << name << std::endl;
        }

        if (vm.count("rename-table"))
        {
            const auto values =
                vm["rename-table"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            std::cout << "operation: "
                      << "rename-table: " << fmt::format("{}", values)
                      << std::endl;
        }
        if (vm.count("list-tables"))
        {
            std::cout << "operation: "
                      << "list-tables " << std::endl;
        }

        if (vm.count("table-add-column"))
        {
            const auto values =
                vm["table-add-column"].as<std::vector<std::string>>();
            assert(values.size() == 3);
            std::cout << "operation: "
                      << "table-add-column: " << fmt::format("{}", values)
                      << std::endl;
        }
        if (vm.count("table-drop-column"))
        {
            const auto values =
                vm["table-drop-column"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            std::cout << "operation: "
                      << "table-drop-column: " << fmt::format("{}", values)
                      << std::endl;
        }
        if (vm.count("table-rename-column"))
        {
            const auto values =
                vm["table-rename-column"].as<std::vector<std::string>>();
            assert(values.size() == 3);
            std::cout << "operation: "
                      << "table-rename-column: " << fmt::format("{}", values)
                      << std::endl;
        }
        if (vm.count("table-list-columns"))
        {
            const auto value = vm["table-list-columns"].as<std::string>();
            std::cout << "operation: "
                      << "table-list-columns: " << value << std::endl;
        }

        if (vm.count("execute"))
        {
            const auto path = vm["execute"].as<std::string>();
            std::cout << "operation: "
                      << "execute: " << path << std::endl;
        }

        if (vm.count("print-database"))
        {
            std::cout << "operation: "
                      << "print-database" << std::endl;
        }
        if (vm.count("print-table"))
        {
            const auto path = vm["print-table"].as<std::string>();
            std::cout << "operation: "
                      << "print-table: " << path << std::endl;
        }
        if (vm.count("print-column"))
        {
            const auto values =
                vm["print-column"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            std::cout << "operation: "
                      << "print-column: " << fmt::format("{}", values)
                      << std::endl;
        }
    }

    int Main(const int count, char **values)
    {
        IOManager io;

        while(true)
        {
            auto&& input = io.ReadUserInput("Input: ");
            if (io.IsEnd(input) == true)
            {
                break;
            }

            io.PrintLine(fmt::format("Your input is: {}", input));
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
