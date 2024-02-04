
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include "database.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using DynamicValue   = Interface::DynamicValue;
    using UDynamicValue  = Interface::UDynamicValue;
    using ITable         = Interface::ITable;
    using UTable         = Interface::UTable;
    using ColumnInfo     = Interface::ColumnInfo;
    using ColumnInfoList = Interface::ColumnInfoList;

    // using ROTRowIndexes = Interface::ROTRowIndexes;
    using Row  = Interface::Row;
    using Data = Interface::RowList;

    struct RowOrientedTableParams
    {
        std::string tableName;
        ColumnInfoList columns;
        Data data;
    };

    class RowOrientedTable : public Interface::IRowOrientedTable
    {
       protected:
        //////////////////////////////////////////////////////////////////

       protected:
        RowOrientedTable(RowOrientedTableParams& params) :
            m_tableName{std::move(params.tableName)},
            m_columns{std::move(params.columns)},
            m_data{std::move(params.data)}
        {
            const int columnCount = RowOrientedTable::ColumnsCount();
            const int rowCount    = RowOrientedTable::RowsCount();

            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
            {
                for (int columnIndex = 0; columnIndex < columnCount;
                     ++columnIndex)
                {
                    if (m_data[rowIndex].size() != columnCount)
                    {
                        fmt::println("vahagn: data-size: {}, columns-count: {}",
                                     m_data[rowIndex].size(), columnCount);
                    }
                    Utility::Assert(m_data[rowIndex].size() == columnCount,
                                    "RowOrientedTable::RowOrientedTable, "
                                    "row-element count != column count");
                }
            }
        }

       public:
        static auto Create(RowOrientedTableParams& params)
            -> Interface::URowOrientedTable
        {
            auto urow =
                Interface::URowOrientedTable{new RowOrientedTable{params}};
            return (urow);
        }

       protected:
       public:
        static auto Create(const std::string& tableName,
                           const ColumnInfoList& columns, const Data& data)
            -> Interface::URowOrientedTable
        {
            const int columnsSize = static_cast<int>(columns.size());

            ColumnInfoList newlist = Interface::CopyColumns(columns);
            Data newdata           = Interface::CopyRowList(data, columnsSize);

            RowOrientedTableParams params;
            params.tableName = tableName;
            params.columns   = std::move(newlist);
            params.data      = std::move(newdata);
            return (Create(params));
        }

        static auto Create(const RowOrientedTable& rowTable)
            -> Interface::URowOrientedTable
        {
            return Create(rowTable.m_tableName, rowTable.m_columns,
                          rowTable.m_data);
        }

       public:
        static auto Create(const ITable& table) -> Interface::URowOrientedTable
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

                for (int columnIndex = 0; columnIndex < columnsCount;
                     ++columnIndex)
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

            return (Create(table.GetName(), columnInfoList, newdata));
        }

       public:
        auto Copy() const -> Interface::URowOrientedTable override
        {
            auto urow = Interface::URowOrientedTable{Create(*this)};
            return urow;
        }
        /*
        test
        this method is not tested
        */
        // auto CopyByIndexes(const ROTRowIndexes& indexes) const
        //     -> Interface::URowOrientedTable override
        // {
        //     const int columnsSize = static_cast<int>(m_columns.size());

        //     ColumnInfoList newlist = Interface::CopyColumns(m_columns);
        //     Data newdata =
        //         Interface::CopyRowList(m_data, columnsSize, indexes);

        //     RowOrientedTableParams params;
        //     params.tableName = m_tableName;
        //     params.columns   = std::move(newlist);
        //     params.data      = std::move(newdata);
        //     return (Create(params));
        // }

       public:
        auto CreateTable() const -> UTable override
        {
            auto table = DataBase::CreateTable(GetTableName());

            const int columnCount = ColumnsCount();
            const int rowCount    = RowsCount();

            for (auto&& columnInfo : m_columns)
            {
                table->AddColumn(
                    DataBase::CreateColumn(columnInfo.name, columnInfo.type));
            }

            for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
            {
                auto&& column = table->GetColumn(columnIndex);
                for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
                {
                    column.AddElement(Interface::CopyUDynValue(
                        GetValue(rowIndex, columnIndex)));
                }
            }

            return table;
        }

       public:
        auto RowsCount() const -> const int override
        {
            return static_cast<int>(m_data.size());
        }
        auto ColumnsCount() const -> const int override
        {
            return static_cast<int>(m_columns.size());
        }

        auto GetTableName() const -> const std::string override
        {
            return m_tableName;
        }
        auto GetColumnInfoList() const -> const ColumnInfoList& override
        {
            return m_columns;
        }

       public:
        auto GetValue(const int rowIndex, const int columnIndex) const
            -> const UDynamicValue& override
        {
            return (m_data.at(rowIndex).at(columnIndex));
        }

       protected:
        std::string m_tableName;
        ColumnInfoList m_columns;
        Data m_data;
    };

    //////////////////////////////////////////////////////////////////////

    auto CreateRowOrientedTable(std::string&& tableName,
                                ColumnInfoList&& columns, Data&& data)
        -> Interface::URowOrientedTable

    {
        return RowOrientedTable::Create(std::move(tableName),
                                        std::move(columns), std::move(data));
    }

    auto CreateRowOrientedTable(const std::string& tableName,
                                const ColumnInfoList& columns, const Data& data)
        -> Interface::URowOrientedTable

    {
        return RowOrientedTable::Create(tableName, columns, data);
    }

    auto CreateRowOrientedTable(const Interface::ITable& table)
        -> Interface::URowOrientedTable

    {
        return RowOrientedTable::Create(table);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
