
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "table.hpp"

#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    Table::Table(const std::string& newname) : m_name{newname}, m_columns{}
    {
    }

    auto Table::Create(const std::string& newname) -> UTable
    {
        Interface::UTable utable{new Table{newname}};
        return (utable);
    }

    auto Table::Copy() const -> UTable
    {
        return Copy(m_name);
    }

    auto Table::Copy(const std::string& newname) const -> UTable
    {
        auto newtable = Create(newname);
        for (auto&& column : m_columns)
        {
            newtable->AddColumn(column->Copy(column->GetName()));
        }
        return newtable;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Table::GetName() const -> const std::string&
    {
        return m_name;
    }
    void Table::SetName(const std::string& name)
    {
        m_name = name;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Table::AddColumn(UColumn column)
    {
        AssertColumnDoesNotExist(column->GetName(), "Table::AddColumn:");
        m_columns.push_back(std::move(column));
    }

    //////////////////////////////////////////////////////////////////////

    bool Table::RemoveColumn(const std::string& columnName)
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

    //////////////////////////////////////////////////////////////////////

    auto Table::GetColumnIndex(const std::string& columnName) const
        -> const std::optional<unsigned int>
    {
        auto begin = m_columns.begin();
        auto end   = m_columns.end();
        auto itr   = std::find_if(begin, end,
                                  [columnName](const Interface::UColumn& column)
                                  {
                                    return column->GetName() == columnName;
                                });
        if (itr == end)
        {
            return std::nullopt;
        }
        return std::make_optional<unsigned int>(std::distance(begin, itr));
    }

    auto Table::GetColumnIndexAssert(const std::string& columnName) const
        -> const unsigned int
    {
        auto&& result = GetColumnIndex(columnName);
        Utility::Assert(result != std::nullopt,
                        "Table::GetColumnIndexAssert: column does not "
                        "exist");
        return *result;
    }

    //////////////////////////////////////////////////////////////////////

    auto Table::GetColumn(const unsigned int index) const -> const IColumn&
    {
        return *m_columns.at(index);
    }
    auto Table::GetColumn(const unsigned int index) -> IColumn&
    {
        return *m_columns.at(index);
    }

    auto Table::GetColumn(const std::string& columnName) const -> const IColumn&
    {
        return (GetColumn(GetColumnIndexAssert(columnName)));
    }
    auto Table::GetColumn(const std::string& columnName) -> IColumn&
    {
        return (GetColumn(GetColumnIndexAssert(columnName)));
    }

    //////////////////////////////////////////////////////////////////////

    void Table::RenameColumn(const std::string& oldColumnName,
                             const std::string& newColumnName)
    {
        auto&& column = GetColumn(oldColumnName);
        column.SetName(newColumnName);
    }

    auto Table::ColumnsCount() const -> const int
    {
        return m_columns.size();
    }

    auto Table::ListColumns() const -> UColumnNameList
    {
        UColumnNameList ulist = std::make_unique<Interface::ColumnNameList>();
        for (auto&& column : m_columns)
        {
            ulist->push_back(column->GetName());
        }
        return ulist;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Table::AssertColumnDoesNotExist(const std::string& columnName,
                                         const std::string& message) const
    {
        auto&& result = GetColumnIndex(columnName);
        Utility::Assert(result == std::nullopt,
                        message + " Table::AssertColumnExist: column exist");
    }

    void Table::AssertColumnExist(const std::string& columnName,
                                  const std::string& message) const
    {
        auto&& result = GetColumnIndex(columnName);
        Utility::Assert(
            result != std::nullopt,
            message + " Table::AssertColumnExist: column does not exist");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
