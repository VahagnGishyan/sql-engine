
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

#include "database/database.hpp"
#include "dir-preparation.hpp"
#include "local-database/db-local-json-stream.hpp"
#include "testing/json-query-parser/dir-preparation.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser::Preparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace
    {

        auto CreateUsersTable() -> Interface::UTable
        {
            auto table = DataBase::CreateTable("users-table");

            auto&& userID =
                DataBase::CreateColumn("user-id", Interface::DynamicType::Int);
            auto&& username = DataBase::CreateColumn(
                "username", Interface::DynamicType::String);
            auto&& password = DataBase::CreateColumn(
                "password", Interface::DynamicType::String);

            userID->AddElement(Interface::CreateUDynValue(1));
            username->AddElement(Interface::CreateUDynValue("John Doe"));
            password->AddElement(
                Interface::CreateUDynValue("hashed-password-1"));

            userID->AddElement(Interface::CreateUDynValue(2));
            username->AddElement(Interface::CreateUDynValue("Alice Smith"));
            password->AddElement(
                Interface::CreateUDynValue("hashed-password-2"));

            userID->AddElement(Interface::CreateUDynValue(3));
            username->AddElement(Interface::CreateUDynValue("Bob Jones"));
            password->AddElement(
                Interface::CreateUDynValue("hashed-password-3"));

            table->AddColumn(std::move(userID));
            table->AddColumn(std::move(username));
            table->AddColumn(std::move(password));

            return table;
        }

        auto CreateTasksTable() -> Interface::UTable
        {
            auto table = DataBase::CreateTable("tasks-table");

            auto&& taskID =
                DataBase::CreateColumn("task-id", Interface::DynamicType::Int);
            auto&& userID =
                DataBase::CreateColumn("user-id", Interface::DynamicType::Int);
            auto&& title =
                DataBase::CreateColumn("title", Interface::DynamicType::String);
            auto&& description = DataBase::CreateColumn(
                "description", Interface::DynamicType::String);
            auto&& dueDate = DataBase::CreateColumn(
                "due-date", Interface::DynamicType::String);
            auto&& status = DataBase::CreateColumn(
                "status", Interface::DynamicType::String);

            taskID->AddElement(Interface::CreateUDynValue(1));
            userID->AddElement(Interface::CreateUDynValue(1));
            title->AddElement(
                Interface::CreateUDynValue("Complete SQL Tutorial"));
            description->AddElement(Interface::CreateUDynValue(
                "Learn SQL basics and advanced queries"));
            dueDate->AddElement(
                Interface::CreateUDynValue("2024-02-29 18:00:00"));
            status->AddElement(Interface::CreateUDynValue("Incomplete"));

            taskID->AddElement(Interface::CreateUDynValue(2));
            userID->AddElement(Interface::CreateUDynValue(2));
            title->AddElement(Interface::CreateUDynValue("Read a Book"));
            description->AddElement(
                Interface::CreateUDynValue("Finish \"The Great Gatsby\""));
            dueDate->AddElement(
                Interface::CreateUDynValue("2024-03-15 20:30:00"));
            status->AddElement(Interface::CreateUDynValue("Incomplete"));

            taskID->AddElement(Interface::CreateUDynValue(3));
            userID->AddElement(Interface::CreateUDynValue(3));
            title->AddElement(Interface::CreateUDynValue("Exercise"));
            description->AddElement(
                Interface::CreateUDynValue("Go for a jog in the park"));
            dueDate->AddElement(
                Interface::CreateUDynValue("2024-02-20 07:00:00"));
            status->AddElement(Interface::CreateUDynValue("Complete"));

            table->AddColumn(std::move(taskID));
            table->AddColumn(std::move(userID));
            table->AddColumn(std::move(title));
            table->AddColumn(std::move(description));
            table->AddColumn(std::move(dueDate));
            table->AddColumn(std::move(status));

            return table;
        }

        auto CreateCategoriesTable() -> Interface::UTable
        {
            auto table = DataBase::CreateTable("categories-table");

            auto&& categoryID = DataBase::CreateColumn(
                "category-id", Interface::DynamicType::Int);
            auto&& categoryName = DataBase::CreateColumn(
                "category-name", Interface::DynamicType::String);

            categoryID->AddElement(Interface::CreateUDynValue(1));
            categoryName->AddElement(Interface::CreateUDynValue("Work"));
            categoryID->AddElement(Interface::CreateUDynValue(2));
            categoryName->AddElement(Interface::CreateUDynValue("Personal"));
            categoryID->AddElement(Interface::CreateUDynValue(3));
            categoryName->AddElement(Interface::CreateUDynValue("Health"));

            table->AddColumn(std::move(categoryID));
            table->AddColumn(std::move(categoryName));

            return table;
        }

        auto CreateTaskCategoriesTable() -> Interface::UTable
        {
            auto table = DataBase::CreateTable("task-categories-table");

            auto&& taskID =
                DataBase::CreateColumn("task-id", Interface::DynamicType::Int);
            auto&& categoryID = DataBase::CreateColumn(
                "category-id", Interface::DynamicType::Int);

            taskID->AddElement(1);
            categoryID->AddElement(1);

            taskID->AddElement(1);
            categoryID->AddElement(2);

            taskID->AddElement(2);
            categoryID->AddElement(2);

            taskID->AddElement(3);
            categoryID->AddElement(3);

            table->AddColumn(std::move(taskID));
            table->AddColumn(std::move(categoryID));

            return table;
        }
    }  // namespace

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void SaveSelectResultCategories(const std::string& path)
    {
        auto database = DataBase::CreateDataBase("select_categories");

        database->AddTable(CreateUsersTable());
        database->AddTable(CreateTasksTable());
        database->AddTable(CreateCategoriesTable());
        database->AddTable(CreateTaskCategoriesTable());

        auto writer = LocalDataBase::CreateDBLocalJSONWriter(path);
        writer->Write(*database);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
