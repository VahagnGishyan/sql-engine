
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <optional>

#include "i-column.hpp"
#include "i-db-object.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ITable;

    using UTable     = std::unique_ptr<ITable>;
    using ShTable    = std::shared_ptr<ITable>;
    using TableList  = std::vector<UTable>;
    using UTableList = std::unique_ptr<TableList>;

    using RowIndexes = std::vector<int>;

    using Row      = std::vector<UDynamicValue>;
    using URow     = std::unique_ptr<Row>;
    using RowList  = std::vector<Row>;
    using URowList = std::unique_ptr<RowList>;

    using TableNameList   = std::vector<std::string>;
    using UTableNameList  = std::unique_ptr<TableNameList>;
    using ShTableNameList = std::shared_ptr<TableNameList>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT ITable : public IDBObject
    {
       public:
        virtual auto Copy() const -> UTable                           = 0;
        virtual auto Copy(const std::string& newname) const -> UTable = 0;
        virtual auto CopyUsingRowIndexes(
            const Interface::RowIndexes& indexes) const -> UTable = 0;
        virtual auto CopyUsingRowIndexes(
            const std::string& newname,
            const Interface::RowIndexes& indexes) const -> UTable = 0;

       public:
        virtual auto GetName() const -> const std::string& = 0;
        virtual void SetName(const std::string& name)      = 0;

       public:
        virtual void AddColumn(UColumn column)                      = 0;
        virtual bool RemoveColumn(const std::string& columnName)    = 0;
        virtual void RenameColumn(const std::string& oldColumnName,
                                  const std::string& newColumnName) = 0;

       public:
        virtual void AddRow(const Row& row)               = 0;
        virtual void RemoveRow(const int rowIndex)        = 0;
        virtual void RemoveRow(const RowIndexes& indexes) = 0;

       public:
        virtual auto GetColumnIndex(const std::string& columnName) const
            -> const std::optional<int>                                 = 0;
        virtual auto GetColumn(const int index) const -> const IColumn& = 0;
        virtual auto GetColumn(const int index) -> IColumn&             = 0;
        virtual auto GetColumn(const std::string& columnName) const
            -> const IColumn&                                             = 0;
        virtual auto GetColumn(const std::string& columnName) -> IColumn& = 0;

       public:
        virtual auto RowsCount() const -> const int                        = 0;
        virtual auto ColumnsCount() const -> const int                     = 0;
        virtual auto ListColumns() const -> UColumnNameList                = 0;
        virtual auto IsColumnExists(const std::string& name) const -> bool = 0;
    };

    //////////////////////////////////////////////////////////////////////

    auto PROJECT_SHARED_EXPORT CreateRowIndexes(const int size) -> RowIndexes;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
