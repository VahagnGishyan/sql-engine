
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "utility.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::LocalDataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateIntColumn() -> Interface::UColumn
    {
        const std::string name{"int-column"};
        constexpr Interface::DynamicType type{Interface::DynamicType::Int};
        auto elements = std::vector<Interface::GetDynamicType<type>::type>{
            0, 41, 874456465, 65465, 485485485, -548548, 48548, -121};

        auto&& column = SQLEngine::DataBase::CreateColumn(name, type);

        for (auto element : elements)
        {
            column->AddElement(Interface::CreateUDynValue(element));
        }

        return column;
    }

    auto CreateDoubleColumn() -> Interface::UColumn
    {
        const std::string name{"double-column"};
        constexpr Interface::DynamicType type{Interface::DynamicType::Double};
        auto elements = std::vector<Interface::GetDynamicType<type>::type>{
            0.45,       41.5,     87445646.5, 65.465,
            48548.5485, -5485.48, 48.548,     -12.1};

        auto&& column = SQLEngine::DataBase::CreateColumn(name, type);

        for (auto element : elements)
        {
            column->AddElement(Interface::CreateUDynValue(element));
        }

        return column;
    }

    auto CreateStringColumn() -> Interface::UColumn
    {
        const std::string name{"string-column"};
        constexpr Interface::DynamicType type{Interface::DynamicType::String};
        auto elements = std::vector<Interface::GetDynamicType<type>::type>{
            "0",          "41",         ",",
            "",           "uijfhbuieu", "uifhdg3uyhhd3478dyhsb$%$^&*",
            " 874456465", "    ",
        };

        auto&& column = SQLEngine::DataBase::CreateColumn(name, type);

        for (auto element : elements)
        {
            column->AddElement(Interface::CreateUDynValue(element));
        }

        return column;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateEmptyTable() -> Interface::UTable
    {
        const std::string name{"empty-table"};
        auto&& table = SQLEngine::DataBase::CreateTable(name);

        return table;
    }

    auto CreateTable() -> Interface::UTable
    {
        auto&& column0 = CreateIntColumn();
        auto&& column1 = CreateDoubleColumn();
        auto&& column2 = CreateStringColumn();

        //////////////////////////////////////////////////////////////////////

        const std::string tablename{"test-table"};

        auto&& table = SQLEngine::DataBase::CreateTable(tablename);

        table->AddColumn(column0->Copy());
        table->AddColumn(column1->Copy());
        table->AddColumn(column2->Copy());

        //////////////////////////////////////////////////////////////////////

        return table;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateListOfTables() -> SQLEngine::Interface::UTableList
    {
        SQLEngine::Interface::UTableList tableList =
            std::make_unique<SQLEngine::Interface::TableList>();

        tableList->push_back(CreateEmptyTable());
        tableList->push_back(CreateTable());

        return tableList;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDataBase() -> SQLEngine::Interface::UDataBase
    {
        const std::string databaseName{"test-database"};
        auto&& database = SQLEngine::DataBase::CreateDataBase(databaseName);

        //////////////////////////////////////////////////////////////////////

        auto tables = Testing::LocalDataBase::CreateListOfTables();

        for (auto&& table : *tables)
        {
            database->AddTable(table->Copy());
        }

        return database;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::LocalDataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
