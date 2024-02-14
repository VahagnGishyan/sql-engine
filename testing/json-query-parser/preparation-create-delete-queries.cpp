
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

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

    auto CreateDeleteTasks(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "delete" operation
        json.put("operation", "delete");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "tasks-table");

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

        auto jsonpath = fmt::format("{}/{}", dir, "delete_tasks.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateDeleteCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "delete" operation
        json.put("operation", "delete");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "categories-table");

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

        auto jsonpath = fmt::format("{}/{}", dir, "delete_categories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateDeleteTaskCategories(const std::string& dir) -> std::string
    {
        // Create the JSON structure
        boost::property_tree::ptree json;

        // Create the "delete" operation
        json.put("operation", "delete");

        // Create the "arguments" subtree
        boost::property_tree::ptree arguments;

        // Populate "arguments" subtree
        arguments.put("from", "task-categories-table");

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

        auto jsonpath = fmt::format("{}/{}", dir, "delete_taskcategories.json");
        // Write the JSON to a file
        boost::property_tree::write_json(jsonpath, json);
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateDeleteQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>
    {
        auto list = std::make_shared<std::vector<std::string>>();

        list->push_back(CreateDeleteTasks(dir));
        list->push_back(CreateDeleteCategories(dir));
        list->push_back(CreateDeleteTaskCategories(dir));

        return list;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
