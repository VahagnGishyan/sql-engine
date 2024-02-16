
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <numeric>

#include "i-column.hpp"
#include "i-database.hpp"
#include "i-db-object.hpp"
#include "i-db-stream.hpp"
#include "i-query.hpp"
#include "i-row-oriented-table.hpp"
#include "i-table.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    void NotImplYet(const std::string& info)
    {
        Utility::Assert(false, "Not impl yet: " + info);
    }

    ColumnInfo::ColumnInfo(const std::string& name, const DynamicType& type) :
        name{name}, type{type}
    {
    }

    //////////////////////////////////////////////////////////////////////

    auto CopyColumns(const ColumnInfoList& columns) -> ColumnInfoList
    {
        ColumnInfoList newlist{};
        for (auto&& columnInfo : columns)
        {
            newlist.emplace_back(columnInfo.name, columnInfo.type);
        }
        return newlist;
    }
    auto CopyRowList(const RowList& data, const int columnsCount) -> RowList
    {
        RowIndexes indexes = Interface::CreateRowIndexes(data.size());
        return CopyRowList(data, columnsCount, indexes);
    }
    auto CopyRowList(const RowList& data, const int columnsCount,
                     const RowIndexes& indexes) -> RowList
    {
        RowList newdata{};
        for (auto&& rowIndex : indexes)
        {
            auto&& row = data[rowIndex];
            Row newrow{};
            Utility::Assert(row.size() == columnsCount,
                            "RowOrientedTable, row.size() == columnsSize");
            newrow.reserve(columnsCount);
            for (auto&& value : row)
            {
                newrow.push_back(Interface::CopyUDynValue(value));
            }
            newdata.push_back(std::move(newrow));
        }
        return newdata;
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateRowIndexes(const int size) -> RowIndexes
    {
        RowIndexes indexes;
        indexes.resize(size);
        std::iota(indexes.begin(), indexes.end(), 0);

        return indexes;
    }

    //////////////////////////////////////////////////////////////////////

    void IQuery::Execute(IDataBase& database) const
    {
        auto&& tablename = GetTableName();
        auto&& table = database.GetTable(tablename);

        auto&& executor = GetQueryExecutor();
        auto&& newTable = executor->Execute(table);

        database.RemoveTable(tablename);
        database.AddTable(std::move(newTable));
    }

    //////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
