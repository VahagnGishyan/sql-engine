
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <vector>

// #include "database/database.hpp"
// #include "db-manager/db-manager.hpp"
// #include "interface/i-table.hpp"
#include "logging/logging.hpp"
// #include "table/table.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Observer
{
    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////

    // class Table : public Interface::ITable
    // {
    //    public:
    //     auto GetInfo() const -> const Interface::WDBObjectInfo override
    //     {
    //         throw std::logic_error("something");
    //     }
    // };

    template <typename Iter>
    void Print(const std::string &title, Iter iter, const Iter end)
    {
        std::cout << title << ": ";
        while (iter != end)
        {
            std::cout << *iter << ' ';
            ++iter;
        }
        std::cout << std::endl;
    }

    int Main(const int count, char **values)
    {
        std::vector<int> vecObj{11, 12, 13, 14, 15, 16, 12, 43, 12, 13, 11};
        Print("Input", vecObj.begin(), vecObj.end());

        auto endIt = std::remove_if(vecObj.begin(), vecObj.end(),
                                    [](const int &elem)
                                    {
                                        return elem % 2 == 0;
                                    });
        // Remove all even numbers collected in the end of vector

        Print("Updated", vecObj.begin(), vecObj.end());
        Print("Updated, front", vecObj.begin(), endIt);
        Print("Updated, end", endIt, vecObj.end());
        vecObj.erase(endIt, vecObj.end());
        Print("Erased", vecObj.begin(), vecObj.end());

        // SQLEngine::Interface::MakeTable<Table>();
        // Table::DoSomething();
        // DataBase::DoSomething();
        // DBManager::DoSomething();

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
