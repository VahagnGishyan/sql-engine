
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

namespace SQLEngine::Testing::JSONQueryParser::Peparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto AddElements = [](boost::property_tree::ptree& rowArray,
                          const std::string& columnName,
                          const std::string& type, const auto& values)
    {
        boost::property_tree::ptree row;

        row.put("column", "task-id");
        row.put("type", "Int");

        boost::property_tree::ptree nodevalues;
        for (auto&& value : values)
        {
            nodevalues.put("", value);
        }
        row.add_child("values", nodevalues);

        rowArray.push_back(std::make_pair("", row));
    };

    auto CreateInsertIntoQueryTasks(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "insert-into" operation
        json.put("operation", "insert-into");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "Tasks");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        AddElements(rowArray, "task-id", "Int", std::vector<int>{4, 5, 6});
        AddElements(rowArray, "user-id", "Int", std::vector<int>{1, 2, 3});
        AddElements(rowArray, "title", "String",
                    std::vector<std::string>{"Prepare Presentation",
                                             "Grocery Shopping", "Run 5K"});
        AddElements(
            rowArray, "description", "String",
            std::vector<std::string>{"Create slides for the meeting",
                                     "Buy groceries for the week",
                                     "Go for a 5-kilometer run in the park"});
        AddElements(rowArray, "due-date", "String",
                    std::vector<std::string>{"2024-03-10 14:00:00",
                                             "2024-02-15 12:30:00",
                                             "2024-03-01 07:30:00"});
        AddElements(
            rowArray, "status", "String",
            std::vector<std::string>{"Incomplete", "Incomplete", "Incomplete"});

        arguments.add_child("row", rowArray);
        json.add_child("arguments", arguments);

        auto jsonpath = fmt::format("{}/{}", dir, "insert_into_tasks.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueryCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "insert-into" operation
        json.put("operation", "insert-into");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "Categories");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        AddElements(rowArray, "category-id", "Int", std::vector<int>{4, 5, 6});
        AddElements(rowArray, "category-name", "String",
                    std::vector<std::string>{"Hobbies", "Education", "Family"});

        arguments.add_child("row", rowArray);
        json.add_child("arguments", arguments);

        auto jsonpath =
            fmt::format("{}/{}", dir, "insert_into_categories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueryTaskCategories(const std::string& dir)
        -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "insert-into" operation
        json.put("operation", "insert-into");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "TaskCategories");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        AddElements(rowArray, "task-id", "Int", std::vector<int>{4, 5, 6});
        AddElements(rowArray, "category-id", "Int", std::vector<int>{4, 5, 6});

        arguments.add_child("row", rowArray);
        json.add_child("arguments", arguments);

        auto jsonpath =
            fmt::format("{}/{}", dir, "insert_into_taskcategories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>
    {
        auto list = std::make_shared<std::vector<std::string>>();

        list->push_back(CreateInsertIntoQueryTasks(dir));
        list->push_back(CreateInsertIntoQueryCategories(dir));
        list->push_back(CreateInsertIntoQueryTaskCategories(dir));

        return list;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::Peparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
