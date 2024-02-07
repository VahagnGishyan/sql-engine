
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "operations.hpp"

#include <fmt/core.h>

#include "condition.hpp"
#include "database/database.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryExecutor
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // ColumnNameAndValue::ColumnNameAndValue(
    //     const std::string& columnName, const Interface::UDynamicValue&
    //     uvalue) : columnName{columnName},
    //     uvalue{Interface::CopyUDynValue(uvalue)}
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class InsertInto : public IOperation
    {
       public:
        InsertInto(InsertIntoData list) : m_data{std::move(list)}
        {
            Utility::Assert(m_data.size() != 0,
                            "InsertInto::InsertInto(list), list is empty");
        }

        auto Execute(const Interface::ITable& table) const
            -> Interface::UTable override
        {
            Utility::Assert(
                m_data.size() == table.ColumnsCount(),
                fmt::format("InsertInto::Execute, data.size = {} and "
                            "table.column-size = {} should be equal",
                            m_data.size(), table.ColumnsCount()));

            auto newTable = table.Copy();
            for (auto&& columnData : m_data)
            {
                auto&& column = newTable->GetColumn(columnData.first /*name*/);
                for (auto&& cell : columnData.second /*list of dynamic values*/)
                {
                    column.AddElement(Interface::CopyUDynValue(cell));
                }
            }
            return newTable;
        }

       protected:
        InsertIntoData m_data;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpInsertInto(InsertIntoData row) -> UOperation
    {
        return std::make_unique<InsertInto>(std::move(row));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ConditionalOperation : public IOperation
    {
       public:
        ConditionalOperation(UCondition condition) :
            m_condition{std::move(condition)}
        {
        }

       public:
        virtual auto Execute(const Interface::ITable& table,
                             const Interface::RowIndexes& indexes) const
            -> Interface::UTable = 0;

        auto Execute(const Interface::ITable& table) const
            -> Interface::UTable override
        {
            Interface::RowIndexes indexes{};
            if (m_condition != nullptr)
            {
                indexes = m_condition->Apply(table);
            }
            else
            {
                indexes = Interface::CreateRowIndexes(table.RowsCount());
            }
            return Execute(table, indexes);
        }

       protected:
        UCondition m_condition;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Select : public ConditionalOperation
    {
       public:
        Select(Interface::ColumnNameList columns, UCondition condition) :
            ConditionalOperation(std::move(condition)),
            m_columns{std::move(columns)}
        {
            Utility::Assert(m_columns.size(),
                            "Select::Select(column-name-list), "
                            "column-name-list must not be empty");
        }

       public:
        auto Execute(const Interface::ITable& table,
                     const Interface::RowIndexes& indexes) const
            -> Interface::UTable override
        {
            auto newTable = DataBase::CreateTable(table.GetName());
            for (auto&& columnName : m_columns)
            {
                newTable->AddColumn(table.GetColumn(columnName).Copy());
            }
            return newTable->CopyUsingRowIndexes(indexes);
        }

       protected:
        Interface::ColumnNameList m_columns;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpSelect(Interface::ColumnNameList columns, UCondition condition)
        -> UOperation
    {
        return std::make_unique<Select>(std::move(columns),
                                        std::move(condition));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Delete : public ConditionalOperation
    {
       public:
        Delete(UCondition condition) :
            ConditionalOperation(std::move(condition))
        {
            Utility::Assert(m_condition != nullptr,
                            "Operation::Delete, condition is nullptr");
        }

       public:
        auto Execute(const Interface::ITable& table,
                     const Interface::RowIndexes& indexes) const
            -> Interface::UTable override
        {
            auto newTable = table.Copy();
            newTable->RemoveRow(indexes);
            return newTable;
        }
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpDelete(UCondition condition) -> UOperation
    {
        return std::make_unique<Delete>(std::move(condition));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Update : public ConditionalOperation
    {
       public:
        Update(UpdateData values, UCondition condition) :
            ConditionalOperation(std::move(condition)),
            m_values{std::move(values)}
        {
        }

       public:
        auto Execute(const Interface::ITable& table,
                     const Interface::RowIndexes& indexes) const
            -> Interface::UTable override
        {
            Utility::Assert(m_values.size() == table.ColumnsCount(),
                            "Update::Execute, values.size and "
                            "table.column-size should be equal");

            auto newTable = table.Copy();
            for (auto&& columninfo : m_values)
            {
                auto&& column = newTable->GetColumn(columninfo.first /*name*/);
                for (auto&& index : indexes)
                {
                    column.GetElement(index) = Interface::CopyUDynValue(
                        columninfo.second /*dynamic values*/);
                }
            }
            return newTable;
        }

       protected:
        UpdateData m_values;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpUpdate(UpdateData values, UCondition condition) -> UOperation
    {
        return std::make_unique<Update>(std::move(values),
                                        std::move(condition));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
