
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-row-oriented-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
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

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT RowOrientedTable
        : public Interface::IRowOrientedTable
    {
        //////////////////////////////////////////////////////////////////

       protected:
        using DynamicValue   = Interface::DynamicValue;
        using UDynamicValue  = Interface::UDynamicValue;
        using ITable         = Interface::ITable;
        using UTable         = Interface::UTable;
        using ColumnInfo     = IRowOrientedTable::ColumnInfo;
        using ColumnInfoList = IRowOrientedTable::ColumnInfoList;

        using Row  = std::vector<UDynamicValue>;
        using Data = std::vector<Row>;

        //////////////////////////////////////////////////////////////////

       protected:
        RowOrientedTable(std::string&& tableName, ColumnInfoList&& columns,
                         Data&& data);

       protected:
        static auto Create(std::string&& tableName, ColumnInfoList&& columns,
                           Data&& data) -> Interface::URowOrientedTable;
        static auto Create(const std::string& tableName,
                           const ColumnInfoList& columns, const Data& data)
            -> Interface::URowOrientedTable;
        static auto Create(const RowOrientedTable& table)
            -> Interface::URowOrientedTable;

       public:
        static auto Create(const ITable& table) -> Interface::URowOrientedTable;

       public:
        auto Copy() const -> Interface::URowOrientedTable override;

       public:
        auto CreateTable() const -> UTable override;

       public:
        auto RowsCount() const -> const int override;
        auto ColumnsCount() const -> const int override;

        auto GetTableName() const -> const std::string override;
        auto GetColumnInfoList() const -> const ColumnInfoList& override;

       public:
        auto GetValue(const int rowIndex, const int columnIndex) const
            -> const UDynamicValue& override;

       protected:
        std::string m_tableName;
        ColumnInfoList m_columns;
        Data m_data;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
