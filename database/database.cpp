
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "database.hpp"

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

    DataBase::DataBase(const std::string& newname) : m_name{newname}, m_tables{}
    {
    }

    auto DataBase::Create(const std::string& newname) -> UDataBase
    {
        Interface::UDataBase udb{new DataBase{newname}};
        return (udb);
    }

    auto DataBase::Copy() const -> UDataBase
    {
        return Copy(m_name);
    }

    auto DataBase::Copy(const std::string& newname) const -> UDataBase
    {
        auto newtable = Create(newname);
        for (auto&& table : m_tables)
        {
            newtable->AddTable(table->Copy(table->GetName()));
        }
        return newtable;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DataBase::GetName() const -> const std::string&
    {
        return m_name;
    }
    void DataBase::SetName(const std::string& name)
    {
        m_name = name;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DataBase::AddTable(UTable table)
    {
        AssertTableNotExists(table->GetName(), "DataBase::AddTable:");
        m_tables.push_back(std::move(table));
    }

    //////////////////////////////////////////////////////////////////////

    void DataBase::RemoveTable(const std::string& tbname)
    {
        auto end    = m_tables.end();
        auto result = std::remove_if(m_tables.begin(), end,
                                     [tbname](const Interface::UTable& table)
                                     {
                                         return table->GetName() == tbname;
                                     });
        m_tables.erase(result, end);
        Utility::Assert(result != end,
                        "DataBase::RemoveTable: table does not exist");
    }

    //////////////////////////////////////////////////////////////////////

    void DataBase::RenameTable(const std::string& oldtbname,
                               const std::string& newtbname)
    {
        auto&& table = GetTable(oldtbname);
        table.SetName(newtbname);
    }

    //////////////////////////////////////////////////////////////////////

    auto DataBase::GetTableIndex(const std::string& tbname) const
        -> const std::optional<unsigned int>
    {
        auto begin = m_tables.begin();
        auto end   = m_tables.end();
        auto itr   = std::find_if(begin, end,
                                  [tbname](const Interface::UTable& table)
                                  {
                                    return table->GetName() == tbname;
                                });
        if (itr == end)
        {
            return std::nullopt;
        }
        return std::make_optional<unsigned int>(std::distance(begin, itr));
    }

    auto DataBase::GetTableIndexAssert(const std::string& tbname,
                                       const std::string& message) const
        -> const unsigned int
    {
        auto&& result = GetTableIndex(tbname);
        Utility::Assert(result != std::nullopt,
                        message +
                            " DataBase::GetTableIndexAssert: table does not "
                            "exist");
        return *result;
    }

    //////////////////////////////////////////////////////////////////////

    auto DataBase::GetTable(const int index) const -> const ITable&
    {
        return *m_tables.at(index);
    }
    auto DataBase::GetTable(const int index) -> ITable&
    {
        return *m_tables.at(index);
    }

    auto DataBase::GetTable(const std::string& tbname) const -> const ITable&
    {
        return (
            GetTable(GetTableIndexAssert(tbname, "DataBase::GetTable const")));
    }
    auto DataBase::GetTable(const std::string& tbname) -> ITable&
    {
        return (
            GetTable(GetTableIndexAssert(tbname, "DataBase::GetTable const")));
    }

    //////////////////////////////////////////////////////////////////////

    auto DataBase::TablesCount() const -> const int
    {
        return m_tables.size();
    }

    auto DataBase::ListTables() const -> UTableNameList
    {
        UTableNameList ulist = std::make_unique<Interface::TableNameList>();
        for (auto&& table : m_tables)
        {
            ulist->push_back(table->GetName());
        }
        return ulist;
    }

    auto DataBase::IsTableExists(const std::string& tbname) const -> bool
    {
        auto&& result = GetTableIndex(tbname);
        return result != std::nullopt;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DataBase::Execute(const Interface::IQuery& query)
    {
        // to do, after impl add tests
        Interface::NotImplYet("DataBase::Execute(query)");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DataBase::AssertTableNotExists(const std::string& tbname,
                                        const std::string& message) const
    {
        auto&& result = GetTableIndex(tbname);
        Utility::Assert(
            result == std::nullopt,
            message + " DataBase::AssertTableNotExists: table exist");
    }

    void DataBase::AssertTableExists(const std::string& tbname,
                                     const std::string& message) const
    {
        auto&& result = GetTableIndex(tbname);
        Utility::Assert(
            result != std::nullopt,
            message + " DataBase::AssertTableExists: table does not exist");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
