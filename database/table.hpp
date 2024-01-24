
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-table.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Table : public Interface::ITable
    {
       protected:
        using DynamicValue = Interface::DynamicValue;
        using ITable       = Interface::ITable;
        using UTable       = Interface::UTable;

        using IColumn         = Interface::IColumn;
        using UColumn         = Interface::UColumn;
        using ColumnList      = Interface::ColumnList;
        using UColumnNameList = Interface::UColumnNameList;

       protected:
        Table(const std::string& newname);

       public:
        static auto Create(const std::string& newname) -> UTable;

       public:
        auto Copy() const -> UTable override;
        auto Copy(const std::string& newname) const -> UTable override;

       public:
        auto GetName() const -> const std::string& override;
        void SetName(const std::string& name) override;

       public:
        void AddColumn(UColumn element) override;
        void RenameColumn(const std::string& oldColumnName,
                          const std::string& newColumnName) override;
        bool RemoveColumn(const std::string& columnName) override;

       public:
        auto GetColumnIndex(const std::string& columnName) const
            -> const std::optional<unsigned int> override;
        auto GetColumnIndexAssert(const std::string& columnName) const -> const
            unsigned int;

       public:
        auto GetColumn(const unsigned int index) const
            -> const IColumn& override;
        auto GetColumn(const unsigned int index) -> IColumn& override;
        auto GetColumn(const std::string& columnName) const
            -> const IColumn& override;
        auto GetColumn(const std::string& columnName) -> IColumn& override;

       public:
        auto ColumnsCount() const -> const int override;
        auto ListColumns() const -> UColumnNameList override;

       public:
        void AssertColumnDoesNotExist(const std::string& columnName,
                                      const std::string& message) const;
        void AssertColumnExist(const std::string& columnName,
                               const std::string& message) const;

       protected:
        std::string m_name;
        ColumnList m_columns;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
