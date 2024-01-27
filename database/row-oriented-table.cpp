
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

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

    using Row  = std::vector<UDynamicValue>;
    using Data = std::vector<Row>;

    class RowOrientedTable : public Interface::IRowOrientedTable
    {
       protected:
        //////////////////////////////////////////////////////////////////

       protected:
        RowOrientedTable(std::string&& tableName, ColumnInfoList&& columns,
                         Data&& data) :
            m_tableName{std::move(tableName)},
            m_columns{std::move(columns)},
            m_data{std::move(data)}
        {
        }

       protected:
        static auto Create(std::string&& tableName, ColumnInfoList&& columns,
                           Data&& data) -> Interface::URowOrientedTable
        {
            auto urow = Interface::URowOrientedTable{
                new RowOrientedTable{std::move(tableName), std::move(columns),
                                     std::move(data)}
            };
            return (urow);
        }

        static auto Create(const std::string& tableName,
                           const ColumnInfoList& columns, const Data& data)
            -> Interface::URowOrientedTable
        {
            const int columnsSize = static_cast<int>(columns.size());

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

            return (Create(std::move(newName), std::move(newlist),
                           std::move(newdata)));
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

            auto tableName = table.GetName();

            return (Create(std::move(tableName), std::move(columnInfoList),
                           std::move(newdata)));
        }

       public:
        auto Copy() const -> Interface::URowOrientedTable override
        {
            auto urow = Interface::URowOrientedTable{Create(*this)};
            return urow;
        }

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
