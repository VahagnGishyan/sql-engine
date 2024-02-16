
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "input-parser.hpp"

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <boost/none.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>

#include "utility/core.hpp"

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

    // void ParseInput(const std::vector<std::string>& arguments)
    void ParseInput(const int count, char** values)
    {
        try
        {
            po::options_description desc("Allowed options");
            desc.add_options()("help", "Prints all commands");
            desc.add_options()("work-dir",
                               "Prints work-dir for connected database");

            // desc.add_options()("init-at", po::value<std::string>(), "path");
            // desc.add_options()("connect-to", po::value<std::string>(),
            // "path"); desc.add_options()(
            //     "disconnect",
            //     po::value<std::optional<std::string>>()->default_value(
            //         std::optional<std::string>{""}),
            //     "optional<path>");

            // desc.add_options()("drop", "drop");
            // desc.add_options()("print", po::value<std::list<std::string>>(),
            //                    "if empty, then prints database, table-name |
            //                    " "table-name column-name");
            // desc.add_options()("rename", po::value<std::string>(),
            //                    "db-new-name");
            // desc.add_options()("add-table", po::value<std::string>(),
            //                    "table-name");
            // desc.add_options()("remove-table", po::value<std::string>(),
            //                    "table-name");

            // desc.add_options()(
            //     "rename-table", po::value<std::string>()->multitoken(),
            //     "table-name table-name-new")("list-tables", "list-tables");
            // desc.add_options()("table-add-column",
            //                    po::value<std::vector<std::string>>(),
            //                    "table-name column-name column-type");
            // desc.add_options()("table-drop-column",
            //                    po::value<std::vector<std::string>>(),
            //                    "table-name column-name");
            // desc.add_options()("table-rename-column",
            //                    po::value<std::vector<std::string>>(),
            //                    "table-name column-name column-name-new");
            // desc.add_options()("table-list-columns",
            //                    po::value<std::vector<std::string>>(),
            //                    "table-name column-name");
            // desc.add_options()("execute", po::value<std::string>(), "path");

            po::variables_map vm;
            po::store(po::parse_command_line(count, values, desc), vm);
            // po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            if (vm.count("help"))
            {
                std::cout << desc << std::endl;
                return;
            }

            if (vm.count("work-dir"))
            {
                std::cout << "operation: "
                          << "work-dir" << std::endl;
                // Handle work-dir command
                return;
            }

            // Continue checking other commands and handle accordingly...
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
