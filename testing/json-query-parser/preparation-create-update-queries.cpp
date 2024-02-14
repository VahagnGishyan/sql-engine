
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

    auto CreateUpdateTasks(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "update" operation
        json.put("operation", "update");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "tasks-table");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        // Populate "row" array
        boost::property_tree::ptree row1;
        row1.put("column", "title");
        row1.put("type", "String");
        row1.put("value", "Updated SQL Tutorial");
        rowArray.push_back(std::make_pair("", row1));

        boost::property_tree::ptree row2;
        row2.put("column", "due-date");
        row2.put("type", "DateTime");
        row2.put("value", "2024-03-05 12:00:00");
        rowArray.push_back(std::make_pair("", row2));

        arguments.add_child("row", rowArray);

        // Create the "where" subtree
        boost::property_tree::ptree whereSubtree;
        whereSubtree.put("condition", "equal");

        // Create the "arguments" subtree within "where"
        boost::property_tree::ptree whereArguments;
        whereArguments.put("column-name", "task-id");
        whereArguments.put("type", "Int");
        whereArguments.put("value", 1);

        whereSubtree.add_child("arguments", whereArguments);

        arguments.add_child("where", whereSubtree);

        json.add_child("arguments", arguments);

        auto jsonpath = fmt::format("{}/{}", dir, "update_tasks.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateUpdateCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "update" operation
        json.put("operation", "update");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "categories-table");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        // Populate "row" array
        boost::property_tree::ptree row;
        row.put("column", "category-name");
        row.put("type", "String");
        row.put("value", "Work (Updated)");
        rowArray.push_back(std::make_pair("", row));

        arguments.add_child("row", rowArray);

        // Create the "where" subtree
        boost::property_tree::ptree whereSubtree;
        whereSubtree.put("condition", "equal");

        // Create the "arguments" subtree within "where"
        boost::property_tree::ptree whereArguments;
        whereArguments.put("column-name", "category-id");
        whereArguments.put("type", "Int");
        whereArguments.put("value", 1);

        whereSubtree.add_child("arguments", whereArguments);

        arguments.add_child("where", whereSubtree);

        json.add_child("arguments", arguments);

        auto jsonpath = fmt::format("{}/{}", dir, "update_categories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateUpdateTaskCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "update" operation
        json.put("operation", "update");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("table-name", "task-categories-table");

        // Create the "row" array
        boost::property_tree::ptree rowArray;

        // Populate "row" array
        boost::property_tree::ptree row1;
        row1.put("column", "task-id");
        row1.put("type", "Int");
        row1.put("value", 1);
        rowArray.push_back(std::make_pair("", row1));

        boost::property_tree::ptree row2;
        row2.put("column", "category-id");
        row2.put("type", "Int");
        row2.put("value", 4);
        rowArray.push_back(std::make_pair("", row2));

        arguments.add_child("row", rowArray);

        // Create the "where" subtree
        boost::property_tree::ptree whereSubtree;
        whereSubtree.put("condition", "equal");

        // Create the "arguments" subtree within "where"
        boost::property_tree::ptree whereArguments;
        whereArguments.put("column-name", "task-id");
        whereArguments.put("type", "Int");
        whereArguments.put("value", 1);

        whereSubtree.add_child("arguments", whereArguments);

        arguments.add_child("where", whereSubtree);

        json.add_child("arguments", arguments);

        auto jsonpath = fmt::format("{}/{}", dir, "update_taskcategories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateUpdateQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>
    {
        auto list = std::make_shared<std::vector<std::string>>();

        list->push_back(CreateUpdateTasks(dir));
        list->push_back(CreateUpdateCategories(dir));
        list->push_back(CreateUpdateTaskCategories(dir));

        return list;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
