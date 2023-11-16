
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/format.h>

#include <iostream>

#include "database/database.hpp"
#include "db-manager/db-manager.hpp"
#include "interface/i-table.hpp"
#include "table/table.hpp"
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

    class Table : public DBLib::Interface::ITable
    {
       public:
        auto GetInfo() const -> const DBLib::Interface::WDBObjectInfo override
        {
            throw std::logic_error("something");
        }
    };

    int Main(const int count, char **values)
    {
        SQLEngine::DBLib::Interface::MakeTable<Table>();
        DBLib::Table::DoSomething();
        DBLib::DataBase::DoSomething();
        DBLib::DBManager::DoSomething();

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
        SQLEngine::Logging::Init();
        SQLEngine::Logging::Info("Program observer.");
        SQLEngine::Logging::Signal("Start Main().");
        SQLEngine::Logging::Signal(fmt::format("log-dir: {}", SQLEngine::Logging::GetLogPath()));
        returnKey = SQLEngine::Observer::Main(argc, argv);
        SQLEngine::Logging::Signal("Close Main().");
    }
    catch (std::exception &err)
    {
        std::cout << std::string("Catch exception, type is std::exception, message is ") + err.what() << std::endl;
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
