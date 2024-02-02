
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "operations.hpp"

#include <fmt/core.h>

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
        InsertInto(Interface::ColumnList list) : m_columns{std::move(list)}
        {
        }

        void Execute(Interface::ITable& table) const override
        {
            for (auto&& column : m_columns)
            {
                table.AddColumn(column->Copy());
            }
        }

        auto ToString(Interface::ITable& table) const -> const std::string
        {
            return "InsertInto";
        }

       protected:
        Interface::ColumnList m_columns;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    template <typename Function>
    auto GetIndexesIf(const Interface::ITable& table, Function func)
    {
        std::vector<int> indexes;
        const int size = table.ColumnsCount();
        for (int index = 0; index < size; ++index)
        {
            auto&& column = table.GetColumn(index);
            if (func(column) == true)
            {
                indexes.push_back(index);
            }
        }
        return (indexes);
    }

    class ConditionalBasedOperation : public IOperation
    {
       public:
        ConditionalBasedOperation(Interface::ColumnList list) :
            m_columns{std::move(list)}
        {
        }

        void Execute(Interface::ITable& table) const override
        {
            for (auto&& column : m_columns)
            {
                table.AddColumn(column->Copy());
            }
        }

        auto ToString(Interface::ITable& table) const -> const std::string
        {
            return "InsertInto";
        }

       protected:
        Interface::ColumnList m_columns;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::QueryExecutor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
