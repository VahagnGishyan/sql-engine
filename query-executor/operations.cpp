
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "operations.hpp"

#include <fmt/core.h>

#include "condition.hpp"
#include "logging/logging.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::QueryExecutor
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class InsertInto : public IOperation
    {
       public:
        InsertInto(Interface::URowList list) : m_data{std::move(list)}
        {
        }

        auto Execute(const Interface::ITable& table) const
            -> Interface::UTable override
        {
            auto newTable = table.Copy();
            for (auto&& row : *m_data)
            {
                newTable->AddRow(row);
            }
            return newTable;
        }

        auto ToString() const -> const std::string override
        {
            return "InsertInto";
        }

       protected:
        Interface::URowList m_data;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateOpInsertInto(Interface::URowList row) -> UOperation
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
                             Interface::RowIndexes& indexes) const
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
        Select(Interface::UColumnList columns, UCondition condition = nullptr) :
            ConditionalOperation(std::move(condition)),
            m_columns{std::move(columns)}
        {
        }

       public:
        auto Execute(const Interface::ITable& table,
                     Interface::RowIndexes& indexes) const
            -> Interface::UTable override
        {
            return table.CopyUsingRowIndexes(indexes);
        }

       public:
        auto ToString() const -> const std::string override
        {
            return "Select";
        }

       protected:
        Interface::UColumnList m_columns;
    };

    // class Select(ConditionalBasedOperation):
    // def __init__(self, column_list: list[Column], condition: Condition =
    // None):
    //     super().__init__(condition)
    //     self.column_list = column_list

    // def execute(self, table: Table) -> Table:
    //     if not self.column_list:
    //         raise ValueError("No columns selected in the query.")

    //     if self.column_list[0] == "*":
    //         self.column_list = table.list_columns()

    //     index_list = self.get_filtered_indexes(table)

    //     result = Table("ResultTable")

    //     for column_name in self.column_list:
    //         column: Column = table.get_column_by_name(column_name).copy()
    //         column.elements = [column.elements[index] for index in
    //         index_list] result.insert_column(column)

    //     return result

    // # for debug
    // def print(self):
    //     console.PrintInfo("[Select]")
    //     print(f"column-list: {self.column_list}")
    //     if self.condition:
    //         print(f"condition: ", end="")
    //         self.condition.print()

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
