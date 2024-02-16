
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <boost/none.hpp>
#include <boost/program_options.hpp>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>

#include "cli-app-manager.hpp"
#include "cli-operations.hpp"
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

    namespace
    {
        //////////////////////////////////////////////////////////////////
        //                                                              //
        //////////////////////////////////////////////////////////////////

        auto GetOptionsDescription() -> po::options_description
        {
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
            desc.add_options()(
                "rename-table",
                po::value<std::vector<std::string>>()->multitoken(),
                "Renames Table, args: table-name new-table-name");
            desc.add_options()("list-tables", "List tables in database");

            desc.add_options()(
                "table-add-column",
                po::value<std::vector<std::string>>()->multitoken(),
                "Adds column in Tale, args: table-name column-name "
                "column-type");
            desc.add_options()(
                "table-drop-column",
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
            desc.add_options()(
                "print-column",
                po::value<std::vector<std::string>>()->multitoken(),
                "Prints column, args: table-name column-name");

            return desc;
        }

        //////////////////////////////////////////////////////////////////
        //                                                              //
        //////////////////////////////////////////////////////////////////

        void CheckInput(const std::vector<std::string>& arguments)
        {
            assert(arguments.empty() == false);
        }

        void CheckParsedData(const po::variables_map& vmap)
        {
            assert(vmap.empty() == false);
        }

        //////////////////////////////////////////////////////////////////
        //                                                              //
        //////////////////////////////////////////////////////////////////

        using jbdh = std::function<std::vector<std::string>()>;

        class OperationMethod : Operation
        {
        };

        //////////////////////////////////////////////////////////////////
        //                                                              //
        //////////////////////////////////////////////////////////////////
    }  // namespace

    UOperation ParseInput(const std::vector<std::string>& arguments)
    {
        //////////////////////////////////////////////////////////////////
        CheckInput(arguments);
        //////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////
        po::command_line_parser parser(arguments);
        po::options_description desc{GetOptionsDescription()};
        parser.options(desc);

        po::variables_map vm;
        po::store(parser.run(), vm);
        po::notify(vm);
        //////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////
        CheckParsedData(vm);
        //////////////////////////////////////////////////////////////////

        if (vm.count("help"))
        {
            std::stringstream stream;
            stream << desc;
            std::vector<std::string> lines;
            std::string line;

            while (std::getline(stream, line))
            {
                lines.push_back(line);
            }

            return CreateOp::Help(std::move(lines));
        }

        if (vm.count("work-dir"))
        {
            return CreateOp::WorkDir();
        }

        if (vm.count("init-at"))
        {
            const std::string path = vm["init-at"].as<std::string>();
            return CreateOp::InitAt(path);
        }
        if (vm.count("connect-to"))
        {
            const std::string path = vm["connect-to"].as<std::string>();
            return CreateOp::ConnectTo(path);
        }
        if (vm.count("disconnect"))
        {
            return CreateOp::Disconnect();
        }
        if (vm.count("disconnect-path"))
        {
            const std::string path = vm["disconnect-path"].as<std::string>();
            return CreateOp::DisconnectPath(path);
        }
        if (vm.count("save-at"))
        {
            const std::string path = vm["save-at"].as<std::string>();
            return CreateOp::SaveAt(path);
        }
        if (vm.count("drop"))
        {
            return CreateOp::Drop();
        }
        if (vm.count("rename"))
        {
            const std::string newName = vm["rename"].as<std::string>();
            return CreateOp::Rename(newName);
        }
        if (vm.count("add-table"))
        {
            const std::string name = vm["add-table"].as<std::string>();
            return CreateOp::AddTable(name);
        }
        if (vm.count("remove-table"))
        {
            const std::string name = vm["remove-table"].as<std::string>();
            return CreateOp::RemoveTable(name);
        }

        if (vm.count("rename-table"))
        {
            auto values =
                vm["rename-table"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            return CreateOp::RenameTable(values[0], values[1]);
        }
        if (vm.count("list-tables"))
        {
            return CreateOp::ListTables();
        }

        if (vm.count("table-add-column"))
        {
            const auto values =
                vm["table-add-column"].as<std::vector<std::string>>();
            assert(values.size() == 3);
            return CreateOp::TableAddColumn(values[0], values[1], values[2]);
        }
        if (vm.count("table-drop-column"))
        {
            const auto values =
                vm["table-drop-column"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            return CreateOp::TableDropColumn(values[0], values[1]);
        }
        if (vm.count("table-rename-column"))
        {
            const auto values =
                vm["table-rename-column"].as<std::vector<std::string>>();
            assert(values.size() == 3);
            return CreateOp::TableRenameColumn(values[0], values[1], values[2]);
        }
        if (vm.count("table-list-columns"))
        {
            const auto value = vm["table-list-columns"].as<std::string>();
            return CreateOp::TableListColumns(value);
        }

        if (vm.count("execute"))
        {
            const auto path = vm["execute"].as<std::string>();
            return CreateOp::Execute(path);
        }

        if (vm.count("print-database"))
        {
            return CreateOp::PrintDataBase();
        }
        if (vm.count("print-table"))
        {
            const auto tablename = vm["print-table"].as<std::string>();
            return CreateOp::PrintTable(tablename);
        }
        if (vm.count("print-column"))
        {
            const auto values =
                vm["print-column"].as<std::vector<std::string>>();
            assert(values.size() == 2);
            return CreateOp::PrintColumn(values[0], values[1]);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
