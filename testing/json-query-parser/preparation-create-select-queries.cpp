
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

    auto CreateSelectTasks(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "select" operation
        json.put("operation", "select");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "tasks-table");

        // Create the "columns" array
        boost::property_tree::ptree columnsArray;
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("task-id")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("user-id")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("title")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("description")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("due-date")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("status")));

        arguments.add_child("columns", columnsArray);

        // Create the "where" subtree
        boost::property_tree::ptree whereSubtree;
        whereSubtree.put("condition", "equal");

        // Create the "arguments" subtree within "where"
        boost::property_tree::ptree whereArguments;
        whereArguments.put("column-name", "status");
        whereArguments.put("type", "Enum");
        whereArguments.put("value", "Incomplete");

        whereSubtree.add_child("arguments", whereArguments);

        arguments.add_child("where", whereSubtree);

        json.add_child("arguments", arguments);

        auto jsonpath =
            fmt::format("{}/{}", dir, "select_tasks_incomplete.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateSelectCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "select" operation
        json.put("operation", "select");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "categories-table");

        // Create the "columns" array
        boost::property_tree::ptree columnsArray;
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("category-id")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("category-name")));

        arguments.add_child("columns", columnsArray);

        // Set "where" to null
        arguments.put_child("where", boost::property_tree::ptree());

        json.add_child("arguments", arguments);

        auto jsonpath = fmt::format("{}/{}", dir, "select_categories_all.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateSelectCategoriesID(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "select" operation
        json.put("operation", "select");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "task-categories-table");

        // Create the "columns" array
        boost::property_tree::ptree columnsArray;
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("task-id")));
        columnsArray.push_back(
            std::make_pair("", boost::property_tree::ptree("category-id")));

        arguments.add_child("columns", columnsArray);

        // Set "where" to null
        arguments.put_child("where", boost::property_tree::ptree());

        json.add_child("arguments", arguments);

        auto jsonpath =
            fmt::format("{}/{}", dir, "select_taskcategories_all.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateSelectQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>
    {
        auto list = std::make_shared<std::vector<std::string>>();

        list->push_back(CreateSelectTasks(dir));
        list->push_back(CreateSelectCategories(dir));
        list->push_back(CreateSelectCategoriesID(dir));

        return list;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
