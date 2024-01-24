
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "row-oriented-table.hpp"

#include "column.hpp"
#include "table.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    RowOrientedTable::RowOrientedTable(std::string&& tableName,
                                       ColumnInfoList&& columns, Data&& data) :
        m_tableName{std::move(tableName)},
        m_columns{std::move(columns)},
        m_data{std::move(data)}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::Create(std::string&& tableName,
                                  ColumnInfoList&& columns, Data&& data)
        -> Interface::URowOrientedTable
    {
        auto urow = Interface::URowOrientedTable{
            new RowOrientedTable{std::move(tableName), std::move(columns),
                                 std::move(data)}
        };
        return (urow);
    }

    auto RowOrientedTable::Create(const std::string& tableName,
                                  const ColumnInfoList& columns,
                                  const Data& data)
        -> Interface::URowOrientedTable
    {
        const int columnsSize = columns.size();

        ColumnInfoList newlist{};
        Data newdata{};

        for (auto&& columnInfo : columns)
        {
            newlist.emplace_back(columnInfo.name, columnInfo.type);
        }

        for (auto&& row : data)
        {
            Row newrow{};
            Utility::Assert(row.size() == columnsSize,
                            "RowOrientedTable, row.size() == columnsSize");
            newrow.reserve(columnsSize);
            for (auto&& value : row)
            {
                newrow.push_back(Interface::CopyUDynValue(value));
            }
            newdata.push_back(std::move(newrow));
        }

        auto newName = tableName;

        return (
            Create(std::move(newName), std::move(newlist), std::move(newdata)));
    }

    auto RowOrientedTable::Create(const RowOrientedTable& rowTable)
        -> Interface::URowOrientedTable
    {
        return Create(rowTable.m_tableName, rowTable.m_columns,
                      rowTable.m_data);
    }

    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::Create(const Interface::ITable& table)
        -> Interface::URowOrientedTable
    {
        ColumnInfoList columnInfoList{};
        Data newdata{};

        auto columnsCount = table.ColumnsCount();
        for (int index = 0; index < columnsCount; ++index)
        {
            auto&& column = table.GetColumn(index);
            columnInfoList.emplace_back(column.GetName(), column.GetType());
        }

        if (columnsCount != 0)
        {
            auto&& elementsCount = table.GetColumn(0).GetSize();
            newdata.resize(elementsCount);

            for (int columnIndex = 0; columnIndex < columnsCount; ++columnIndex)
            {
                auto&& column = table.GetColumn(columnIndex);
                for (int rowIndex = 0; rowIndex < elementsCount; ++rowIndex)
                {
                    newdata[rowIndex].resize(columnsCount);
                    auto&& columnElement = column.GetElement(rowIndex);
                    newdata[rowIndex][columnIndex] =
                        Interface::CopyUDynValue(columnElement);
                }
            }
        }

        auto tableName = table.GetName();

        return (Create(std::move(tableName), std::move(columnInfoList),
                       std::move(newdata)));
    }

    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::Copy() const -> Interface::URowOrientedTable
    {
        auto urow = Interface::URowOrientedTable{Create(*this)};
        return urow;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::CreateTable() const -> Interface::UTable
    {
        auto table = Table::Create(GetTableName());

        const int columnCount = ColumnsCount();
        const int rowCount    = RowsCount();

        Interface::ColumnList columnList{};
        columnList.reserve(columnCount);
        for (auto&& columnInfo : m_columns)
        {
            columnList.push_back(
                Column::Create(columnInfo.name, columnInfo.type));
        }

        for (int columnIndex = 0; columnCount; ++columnIndex)
        {
            auto&& column = table->GetColumn(columnIndex);
            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
            {
                column.AddElement(
                    Interface::CopyUDynValue(GetValue(rowIndex, columnIndex)));
            }
        }

        return table;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::RowsCount() const -> const int
    {
        return m_columns.size();
    }
    auto RowOrientedTable::ColumnsCount() const -> const int
    {
        return m_tableName.size();
    }

    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::GetTableName() const -> const std::string
    {
        return m_tableName;
    }

    auto RowOrientedTable::GetColumnInfoList() const -> const ColumnInfoList&
    {
        return m_columns;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowOrientedTable::GetValue(const int rowIndex,
                                    const int columnIndex) const
        -> const UDynamicValue&
    {
        return (m_data.at(rowIndex).at(columnIndex));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
