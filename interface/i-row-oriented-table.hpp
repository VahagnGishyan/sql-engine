
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

    using URowOrientedTable  = std::unique_ptr<IRowOrientedTable>;
    using ShRowOrientedTable = std::shared_ptr<IRowOrientedTable>;
    using RowList            = std::vector<URowOrientedTable>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IRowOrientedTable : public IDBObject
    {
       public:
        struct ColumnInfo
        {
            ColumnInfo(const std::string& name, const DynamicType& type);
            std::string name;
            DynamicType type;
        };
        using ColumnInfoList = std::vector<ColumnInfo>;

       public:
        virtual auto Copy() const -> URowOrientedTable = 0;

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
