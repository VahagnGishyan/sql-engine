
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-object.hpp"
#include "i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IRowOrientedTable;

    using URowOrientedTable    = std::unique_ptr<IRowOrientedTable>;
    using ShRowOrientedTable   = std::shared_ptr<IRowOrientedTable>;
    using RowOrientedTableList = std::vector<URowOrientedTable>;

    //////////////////////////////////////////////////////////////////////

    struct PROJECT_SHARED_EXPORT ColumnInfo
    {
        ColumnInfo(const std::string& name, const DynamicType& type);
        std::string name;
        DynamicType type;
    };
    using ColumnInfoList = std::vector<ColumnInfo>;

    using ROTRowIndexes = std::vector<int>;

    using ROTRow     = std::vector<UDynamicValue>;
    using ROTRowList = std::vector<ROTRow>;

    auto PROJECT_SHARED_EXPORT CopyColumns(const ColumnInfoList& columns)
        -> ColumnInfoList;
    auto PROJECT_SHARED_EXPORT CopyROTRowList(const ROTRowList& data,
                                              const int columnsCount)
        -> ROTRowList;
    auto PROJECT_SHARED_EXPORT CopyROTRowList(const ROTRowList& data,
                                              const int columnsCount,
                                              const ROTRowIndexes& indexes)
        -> ROTRowList;

    //////////////////////////////////////////////////////////////////////

    /*
    Structure of the class RowOrientedTable

    RowOrientedTable contains the following information:

    - Table name

    - List of columns, where each column is represented by two fields: name
        and data type. The order of columns corresponds to their order in
    the table.

    - Data
        Data represents a list of Rows.
        RowOrientedTable is also a list containing values of type
    DynamicValue. Initially, the number of values in a RowOrientedTable
    always corresponds to the number of elements in the list of columns. The
    order of values in a RowOrientedTable is important. For example, the 3th
    element in a row belongs to the column with number 3 in the list of
    columns.

    Functionality of RowOrientedTable:
    * Can only be created from an existing table.
    * Allows saving data in a Row-Oriented table.
    * Ensures the ability to read data but NOT to modify it.
    * Can create a table identical to the one from which it was created
      based on the existing data.
    */

    class PROJECT_SHARED_EXPORT IRowOrientedTable : public IDBObject
    {
       public:
        virtual auto Copy() const -> URowOrientedTable = 0;
        virtual auto CopyByIndexes(const ROTRowIndexes&) const
            -> URowOrientedTable = 0;

       public:
        virtual auto CreateTable() const -> UTable = 0;

       public:
        virtual auto RowsCount() const -> const int    = 0;
        virtual auto ColumnsCount() const -> const int = 0;

        virtual auto GetTableName() const -> const std::string          = 0;
        virtual auto GetColumnInfoList() const -> const ColumnInfoList& = 0;

       public:
        virtual auto GetValue(const int rowIndex, const int columnIndex) const
            -> const UDynamicValue& = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
