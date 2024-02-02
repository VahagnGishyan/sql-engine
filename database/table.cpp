
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <numeric>

#include "database.hpp"
#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using DynamicValue = Interface::DynamicValue;
    using ITable       = Interface::ITable;
    using UTable       = Interface::UTable;

    using IColumn         = Interface::IColumn;
    using UColumn         = Interface::UColumn;
    using ColumnList      = Interface::ColumnList;
    using UColumnNameList = Interface::UColumnNameList;

    //////////////////////////////////////////////////////////////////////

    class Table : public Interface::ITable
    {
       protected:
        Table(const std::string& newname) : m_name{newname}, m_columns{}
        {
        }

       public:
        static auto Create(const std::string& newname) -> UTable
        {
            Interface::UTable utable{new Table{newname}};
            return (utable);
        }

       public:
        auto Copy() const -> UTable override
        {
            return Copy(m_name);
        }
        auto Copy(const std::string& newname) const -> UTable override
        {
            Interface::RowIndexes indexes;
            indexes.resize(RowsCount());
            std::iota(indexes.begin(), indexes.end(), 0);

            return (CopyUsingRowIndexes(newname, indexes));
        }
        auto CopyUsingRowIndexes(
            const Interface::RowIndexes& indexes) const -> UTable override
        {            
            return (CopyUsingRowIndexes(m_name, indexes));
        }
        auto CopyUsingRowIndexes(
            const std::string& newname,
            const Interface::RowIndexes& indexes) const -> UTable override
        {
            auto newtable = Create(newname);
            for (auto&& column : m_columns)
            {
                auto&& newcolumn =
                    CreateColumn(column->GetName(), column->GetType());
                for (auto index : indexes)
                {
                    newcolumn->AddElement(
                        Interface::CopyUDynValue(column->GetElement(index)));
                }
                newtable->AddColumn(std::move(newcolumn));
            }
            return newtable;
        }

       public:
        auto GetName() const -> const std::string& override
        {
            return m_name;
        }
        void SetName(const std::string& name) override
        {
            m_name = name;
        }

       public:
        void AddColumn(UColumn column) override
        {
            AssertColumnDoesNotExist(column->GetName(), "AddColumn:");
            if (ColumnsCount() != 0)
            {
                Utility::Assert(
                    RowsCount() == column->GetSize(),
                    "AddColumn, columns count must be equal in table:");
            }
            m_columns.push_back(std::move(column));
        }
        void RenameColumn(const std::string& oldColumnName,
                          const std::string& newColumnName) override
        {
            auto&& column = GetColumn(oldColumnName);
            column.SetName(newColumnName);
        }
        bool RemoveColumn(const std::string& columnName) override
        {
            auto end = m_columns.end();
            auto result =
                std::remove_if(m_columns.begin(), end,
                               [columnName](const Interface::UColumn& column)
                               {
                                   return column->GetName() == columnName;
                               });
            m_columns.erase(result, end);
            return result != end;
        }

       public:
        auto GetColumnIndex(const std::string& columnName) const
            -> const std::optional<int> override
        {
            auto begin = m_columns.begin();
            auto end   = m_columns.end();
            auto itr =
                std::find_if(begin, end,
                             [columnName](const Interface::UColumn& column)
                             {
                                 return column->GetName() == columnName;
                             });
            if (itr == end)
            {
                return std::nullopt;
            }
            return std::make_optional<int>(
                static_cast<int>(std::distance(begin, itr)));
        }
        auto GetColumnIndexAssert(const std::string& columnName) const -> const
            int
        {
            auto&& result = GetColumnIndex(columnName);
            Utility::Assert(result != std::nullopt,
                            "GetColumnIndexAssert: column does not "
                            "exist");
            return *result;
        }

       public:
        auto GetColumn(const int index) const -> const IColumn& override
        {
            return *m_columns.at(index);
        }
        auto GetColumn(const int index) -> IColumn& override
        {
            return *m_columns.at(index);
        }

        auto GetColumn(const std::string& columnName) const
            -> const IColumn& override
        {
            return (GetColumn(GetColumnIndexAssert(columnName)));
        }
        auto GetColumn(const std::string& columnName) -> IColumn& override
        {
            return (GetColumn(GetColumnIndexAssert(columnName)));
        }

       public:
        auto ColumnsCount() const -> const int override
        {
            return static_cast<int>(m_columns.size());
        }
        auto RowsCount() const -> const int override
        {
            if (ColumnsCount() == 0)
            {
                return 0;
            }
            return m_columns[0]->GetSize();
        }

        auto ListColumns() const -> UColumnNameList override
        {
            UColumnNameList ulist =
                std::make_unique<Interface::ColumnNameList>();
            for (auto&& column : m_columns)
            {
                ulist->push_back(column->GetName());
            }
            return ulist;
        }

        auto IsColumnExists(const std::string& name) const -> bool override
        {
            auto&& result = GetColumnIndex(name);
            return result != std::nullopt;
        }

       public:
        void AssertColumnDoesNotExist(const std::string& columnName,
                                      const std::string& message) const
        {
            auto&& result = GetColumnIndex(columnName);
            Utility::Assert(result == std::nullopt,
                            message + " AssertColumnExist: column exist");
        }

        void AssertColumnExist(const std::string& columnName,
                               const std::string& message) const
        {
            auto&& result = GetColumnIndex(columnName);
            Utility::Assert(
                result != std::nullopt,
                message + " AssertColumnExist: column does not exist");
        }

       protected:
        std::string m_name;
        ColumnList m_columns;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateTable(const std::string& name) -> Interface::UTable
    {
        return Table::Create(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
