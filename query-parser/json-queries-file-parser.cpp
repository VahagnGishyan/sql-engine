
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "json-queries-template.hpp"
#include "parsers.hpp"
#include "query/executors.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryParser
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateCondition(const boost::property_tree::ptree& root)
        -> Query::UCondition;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateCondition(const std::string& condstr,
                         const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        auto columnName = root.get<std::string>(COND_COMPARISON_COLUMN);
        auto columnType = root.get<std::string>(COND_COMPARISON_TYPE);
        SQLEngine::Interface::UDynamicValue value{};

        auto dynType = Interface::ConvertStringToDynamicType(columnType);
        if (dynType == Interface::DynamicType::Int)
        {
            Interface::GetDynamicType<Interface::DynamicType::Int>::type
                cellValue = root.get<Interface::GetDynamicType<
                    Interface::DynamicType::Int>::type>(COND_COMPARISON_VALUE);
            value         = Interface::CreateUDynValue(cellValue);
        }
        if (dynType == Interface::DynamicType::Double)
        {
            Interface::GetDynamicType<Interface::DynamicType::Double>::type
                cellValue = root.get<Interface::GetDynamicType<
                    Interface::DynamicType::Double>::type>(
                    COND_COMPARISON_VALUE);
            value = Interface::CreateUDynValue(cellValue);
        }
        if (dynType == Interface::DynamicType::String)
        {
            Interface::GetDynamicType<Interface::DynamicType::String>::type
                cellValue = root.get<Interface::GetDynamicType<
                    Interface::DynamicType::String>::type>(
                    COND_COMPARISON_VALUE);
            value = Interface::CreateUDynValue(cellValue);
        }

        if (condstr == CONDITION_NAME_EQUAL)
        {
            return Query::CreateConditionEqual(columnName, value);
        }
        if (condstr == CONDITION_NAME_NOT_EQUAL)
        {
            return Query::CreateConditionNotEqual(columnName, value);
        }
        if (condstr == CONDITION_NAME_GREATER_THAN)
        {
            return Query::CreateConditionGreaterThan(columnName, value);
        }
        if (condstr == CONDITION_NAME_LESS_THAN)
        {
            return Query::CreateConditionLessThan(columnName, value);
        }
        if (condstr == CONDITION_NAME_GREATER_THAN_OR_EQUAL)
        {
            return Query::CreateConditionGreaterThanOrEqualTo(columnName,
                                                              value);
        }
        if (condstr == CONDITION_NAME_LESS_THAN_OR_EQUAL)
        {
            return Query::CreateConditionLessThanOrEqualTo(columnName, value);
        }

        throw std::logic_error{fmt::format(
            "CreateCondition(cond-name, root): Unknown condition name: {}",
            condstr)};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateConditionAnd(const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        auto left  = CreateCondition(root.get_child(
            fmt::format("{}.{}", CONDITION_ARGS, CONDITION_LOGICAL_ARG_LEFT)));
        auto right = CreateCondition(root.get_child(
            fmt::format("{}.{}", CONDITION_ARGS, CONDITION_LOGICAL_ARG_RIGHT)));

        return Query::CreateConditionAnd(std::move(left), std::move(right));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateConditionOr(const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        auto left = CreateCondition(root.get_child(CONDITION_LOGICAL_ARG_LEFT));
        auto right =
            CreateCondition(root.get_child(CONDITION_LOGICAL_ARG_RIGHT));

        return Query::CreateConditionOr(std::move(left), std::move(right));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateConditionNot(const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        return Query::CreateConditionNot(CreateCondition(root));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateCondition(const boost::property_tree::ptree& root)
        -> Query::UCondition
    {
        auto condName = root.get<std::string>(CONDITION_NAME);
        auto&& args   = root.get_child(CONDITION_ARGS);
        if (condName == CONDITION_NAME_AND)
        {
            return CreateConditionAnd(args);
        }
        if (condName == CONDITION_NAME_OR)
        {
            return CreateConditionOr(args);
        }
        if (condName == CONDITION_NAME_NOT)
        {
            return CreateConditionNot(args);
        }
        return CreateCondition(condName, args);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateQuerySelectFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        Interface::ColumnNameList columns{};
        for (const auto& column : arguments.get_child(OP_SELECT_COLUMNS))
        {
            columns.push_back(column.second.get_value<std::string>());
        }

        const std::string tableName =
            arguments.get<std::string>(OP_SELECT_FROM);

        auto&& opCond = arguments.get_child_optional(OP_SELECT_WHERE);
        Query::UCondition condition;
        if (opCond.has_value())
        {
            condition = CreateCondition(*opCond);
        }

        return Query::CreateQuery(
            tableName,
            Query::CreateOpSelect(std::move(columns), std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryInsertIntoFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        const std::string tableName =
            arguments.get<std::string>(OP_INSERT_INTO_TABLE);

        Query::InsertIntoData rows{};
        for (const auto& column : arguments.get_child(OP_INSERT_INTO_ROW))
        {
            std::string columnName =
                column.second.get<std::string>(OP_INSERT_INTO_COLUMN_NAME);
            std::string columnType =
                column.second.get<std::string>(OP_INSERT_INTO_COLUMN_TYPE);

            auto dynType = Interface::ConvertStringToDynamicType(columnType);

            for (const auto& value :
                 column.second.get_child(OP_INSERT_INTO_COLUMN_VALUES))
            {
                if (dynType == Interface::DynamicType::Int)
                {
                    Interface::GetDynamicType<Interface::DynamicType::Int>::type
                        cellValue = value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::Int>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
                if (dynType == Interface::DynamicType::Double)
                {
                    Interface::GetDynamicType<
                        Interface::DynamicType::Double>::type cellValue =
                        value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::Double>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
                if (dynType == Interface::DynamicType::String)
                {
                    Interface::GetDynamicType<
                        Interface::DynamicType::String>::type cellValue =
                        value.second.get<Interface::GetDynamicType<
                            Interface::DynamicType::String>::type>("");
                    rows[columnName].push_back(
                        Interface::CreateUDynValue(cellValue));
                }
            }
        }

        // fmt::println("vgihsyan-insert-parser: rows = [");
        // for (auto&& element : rows)
        // {
        //     std::vector<std::string> strvalues{};
        //     auto&& values = element.second;
        //     for (auto&& value : values)
        //     {
        //         strvalues.push_back(Interface::ConvertUDynValueToString(value));
        //     }
        //     fmt::println("\t{}: {}", element.first, strvalues);
        // }
        // fmt::println("]");

        return Query::CreateQuery(tableName,
                                  Query::CreateOpInsertInto(std::move(rows)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryUpdateFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        Query::UpdateData data{};
        const std::string tableName =
            arguments.get<std::string>(OP_UPDATE_TABLE);

        for (const auto& cell : arguments.get_child(OP_INSERT_INTO_ROW))
        {
            std::string columnName =
                cell.second.get<std::string>(OP_UPDATE_CELL_COLUMN);
            std::string columnType =
                cell.second.get<std::string>(OP_UPDATE_CELL_TYPE);
            // fmt::println("vgishyan-update: value = {}.", value);

            auto dynType = Interface::ConvertStringToDynamicType(columnType);
            if (dynType == Interface::DynamicType::Int)
            {
                Interface::GetDynamicType<Interface::DynamicType::Int>::type
                    cellValue = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::Int>::type>(
                        OP_UPDATE_CELL_VALUE);
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
            else if (dynType == Interface::DynamicType::Double)
            {
                Interface::GetDynamicType<Interface::DynamicType::Double>::type
                    cellValue = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::Double>::type>(
                        OP_UPDATE_CELL_VALUE);
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
            else if (dynType == Interface::DynamicType::String)
            {
                Interface::GetDynamicType<Interface::DynamicType::String>::type
                    cellValue = cell.second.get<Interface::GetDynamicType<
                        Interface::DynamicType::String>::type>(
                        OP_UPDATE_CELL_VALUE);
                data[columnName] = Interface::CreateUDynValue(cellValue);
            }
        }

        // fmt::println("vgihsyan-update-parser: data = [");
        // for (auto&& element : data)
        // {
        // fmt::println("\t{}: {}", element.first,
        //              Interface::ConvertUDynValueToString(element.second));
        // }
        // fmt::println("]");

        auto&& condition =
            CreateCondition(arguments.get_child(OP_UPDATE_WHERE));

        return Query::CreateQuery(
            tableName,
            Query::CreateOpUpdate(std::move(data), std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryDeleteFromJSONFile(
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        const std::string tableName =
            arguments.get<std::string>(OP_DELETE_FROM);
        auto&& condition =
            CreateCondition(arguments.get_child(OP_DELETE_WHERE));

        return Query::CreateQuery(tableName,
                                  Query::CreateOpDelete(std::move(condition)));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateQueryExecutorFromJSONFile(
        const std::string& operation,
        const boost::property_tree::ptree& arguments) -> Interface::UQuery
    {
        if (operation == OP_SELECT)
        {
            return CreateQuerySelectFromJSONFile(arguments);
        }
        if (operation == OP_INSERT_INTO)
        {
            return CreateQueryInsertIntoFromJSONFile(arguments);
        }
        if (operation == OP_UPDATE)
        {
            return CreateQueryUpdateFromJSONFile(arguments);
        }
        if (operation == OP_DELETE)
        {
            return CreateQueryDeleteFromJSONFile(arguments);
        }

        throw std::logic_error{
            fmt::format("CreateQueryExecutorFromJSONFile: Unknown operation {}",
                        operation)};
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateQueryExecutorFromJSONFile(const std::string& filepath)
        -> Interface::UQuery
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(filepath, pt);

        std::string operation = pt.get<std::string>(QUERY_OPERATION);
        auto&& arguments      = pt.get_child(QUERY_ARGUMENTS);

        return CreateQueryExecutorFromJSONFile(operation, arguments);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateFromJSONFile(const std::string& filepath) -> Interface::UQuery
    {
        Utility::AssertFileExtension(filepath, ".json");
        Utility::AssertFileExists(filepath);
        return CreateQueryExecutorFromJSONFile(filepath);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryParser

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
