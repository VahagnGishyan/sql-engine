
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

    using UTable    = std::unique_ptr<ITable>;
    using ShTable   = std::shared_ptr<ITable>;
    using TableList = std::vector<UTable>;
    using UTableList = std::unique_ptr<TableList>;

    using TableNameList   = std::vector<std::string>;
    using UTableNameList  = std::unique_ptr<TableNameList>;
    using ShTableNameList = std::shared_ptr<TableNameList>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT ITable : public IDBObject
    {
       public:
        virtual auto Copy() const -> UTable                           = 0;
        virtual auto Copy(const std::string& newname) const -> UTable = 0;

       public:
        virtual auto GetName() const -> const std::string& = 0;
        virtual void SetName(const std::string& name)      = 0;

       public:
        virtual void AddColumn(UColumn column)                      = 0;
        virtual bool RemoveColumn(const std::string& columnName)    = 0;
        virtual void RenameColumn(const std::string& oldColumnName,
                                  const std::string& newColumnName) = 0;

       public:
        virtual auto GetColumnIndex(const std::string& columnName) const
            -> const std::optional<unsigned int> = 0;
        virtual auto GetColumn(const unsigned int index) const
            -> const IColumn&                                        = 0;
        virtual auto GetColumn(const unsigned int index) -> IColumn& = 0;
        virtual auto GetColumn(const std::string& columnName) const
            -> const IColumn&                                             = 0;
        virtual auto GetColumn(const std::string& columnName) -> IColumn& = 0;

       public:
        virtual auto ColumnsCount() const -> const int      = 0;
        virtual auto ListColumns() const -> UColumnNameList = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
