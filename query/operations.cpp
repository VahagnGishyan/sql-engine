
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include "condition.hpp"
#include "database/database.hpp"
#include "executors.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Query
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using IQueryExecutor = Interface::IQueryExecutor;
    using UQueryExecutor = Interface::UQueryExecutor;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class InsertInto : public IQueryExecutor
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
                fmt::format("InsertInto::Execute, and table.column-size = {} "
                            "data.size = {} should be equal",
                            table.ColumnsCount(), m_data.size()));

            auto newTable = table.Copy();
            for (auto&& columnData : m_data)
            {
                auto&& column = newTable->GetColumn(columnData.first /*name*/);
                for (auto&& cell :
                     columnData.second /*vector of dynamic values*/)
                {
                    column.AddElement(Interface::CopyUDynValue(cell));
                }
            }
            return newTable;
        }

        auto Copy() -> UQueryExecutor override
        {
            return CreateOpInsertInto(CopyInsertIntoData(m_data));
        }

       protected:
        InsertIntoData m_data;
    };

    //////////////////////////////////////////////////////////////////////

    auto CopyInsertIntoData(const InsertIntoData& original) -> InsertIntoData
    {
        InsertIntoData newdata{};
        for (auto&& columnData : original)
        {
            auto&& newrow = newdata[columnData.first];
            for (auto&& cell : columnData.second /*vector of dynamic values*/)
            {
                newrow.push_back(Interface::CopyUDynValue(cell));
            }
        }
        return newdata;
    }

    auto CreateOpInsertInto(InsertIntoData row) -> UQueryExecutor
    {
        return std::make_unique<InsertInto>(std::move(row));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ConditionalOperation : public IQueryExecutor
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

        auto Copy() -> UQueryExecutor override
        {
            UCondition copy{};
            if (m_condition != nullptr)
            {
                copy =  m_condition->Copy();
            }
            return CreateOpSelect(m_columns, std::move(copy));
        }

       protected:
        Interface::ColumnNameList m_columns;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpSelect(Interface::ColumnNameList columns, UCondition condition)
        -> UQueryExecutor
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

        auto Copy() -> UQueryExecutor override
        {
            return CreateOpDelete(m_condition->Copy());
        }
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpDelete(UCondition condition) -> UQueryExecutor
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
            Utility::Assert(m_values.size() <= table.ColumnsCount(),
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

        auto Copy() -> UQueryExecutor override
        {
            return CreateOpUpdate(CopyUpdateData(m_values),
                                  m_condition->Copy());
        }

       protected:
        UpdateData m_values;
    };

    //////////////////////////////////////////////////////////////////////

    auto CopyUpdateData(const UpdateData& original) -> UpdateData
    {
        UpdateData newdata{};
        for (auto&& columninfo : original)
        {
            newdata[columninfo.first] =
                Interface::CopyUDynValue(columninfo.second);
        }
        return newdata;
    }

    auto CreateOpUpdate(UpdateData values, UCondition condition)
        -> UQueryExecutor
    {
        return std::make_unique<Update>(std::move(values),
                                        std::move(condition));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Query

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
