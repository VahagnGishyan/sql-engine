
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <sstream>

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

    auto WriteInFile(const std::string& context, const std::string& path,
                     const std::string& name) -> std::string
    {
        auto jsonpath = fmt::format("{}/{}.json", path, name);

        Utility::MakeEmptyFile(jsonpath);
        std::ofstream outputFile(jsonpath);
        Utility::Assert(
            outputFile.is_open(),
            fmt::format("SQLEngine::Testing::JSONQueryParser::Preparation::"
                        "WriteInFile(), can't open file: {}",
                        jsonpath));
        outputFile << context;
        return jsonpath;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueryTasks(const std::string& dir) -> std::string
    {
        std::string jsonString = R"(
            {
                "operation": "insert-into",
                "arguments": {
                    "table-name": "tasks-table",
                    "row": [
                        {
                            "column": "task-id",
                            "type": "Int",
                            "values": [
                                4,
                                5,
                                6
                            ]
                        },
                        {
                            "column": "user-id",
                            "type": "Int",
                            "values": [
                                1,
                                2,
                                3
                            ]
                        },
                        {
                            "column": "title",
                            "type": "String",
                            "values": [
                                "Prepare Presentation",
                                "Grocery Shopping",
                                "Run 5K"
                            ]
                        },
                        {
                            "column": "description",
                            "type": "String",
                            "values": [
                                "Create slides for the meeting",
                                "Buy groceries for the week",
                                "Go for a 5-kilometer run in the park"
                            ]
                        },
                        {
                            "column": "due-date",
                            "type": "String",
                            "values": [
                                "2024-03-10 14:00:00",
                                "2024-02-15 12:30:00",
                                "2024-03-01 07:30:00"
                            ]
                        },
                        {
                            "column": "status",
                            "type": "String",
                            "values": [
                                "Incomplete",
                                "Incomplete",
                                "Incomplete"
                            ]
                        }
                    ]
                }
            }
        )";

        std::string tableName = "insert_into_tasks";
        return WriteInFile(jsonString, dir, tableName);
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueryCategories(const std::string& dir) -> std::string
    {
        std::string jsonString = R"(
            {
                "operation": "insert-into",
                "arguments": {
                    "table-name": "categories-table",
                    "row": [
                        {
                            "column": "category-id",
                            "type": "Int",
                            "values": [
                                4,
                                5,
                                6
                            ]
                        },
                        {
                            "column": "category-name",
                            "type": "String",
                            "values": [
                                "Hobbies",
                                "Education",
                                "Family"
                            ]
                        }
                    ]
                }
            }
        )";

        std::string tableName = "insert_into_categories";
        return WriteInFile(jsonString, dir, tableName);
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateInsertIntoQueryTaskCategories(const std::string& dir)
        -> std::string
    {
        std::string jsonString = R"(
            {
                "operation": "insert-into",
                "arguments": {
                    "table-name": "task-categories-table",
                    "row": [
                        {
                            "column": "task-id",
                            "type": "Int",
                            "values": [
                                4,
                                5,
                                6
                            ]
                        },
                        {
                            "column": "category-id",
                            "type": "Int",
                            "values": [
                                4,
                                5,
                                6
                            ]
                        }
                    ]
                }
            }
        )";

        std::string tableName = "insert_into_taskcategories";
        return WriteInFile(jsonString, dir, tableName);
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
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
