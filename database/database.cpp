
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "database.hpp"

#include <fmt/core.h>

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

    using ITable         = Interface::ITable;
    using UTable         = Interface::UTable;
    using TableList      = Interface::TableList;
    using UTableNameList = Interface::UTableNameList;

    using IDataBase = Interface::IDataBase;
    using UDataBase = Interface::UDataBase;

    using IQueryExecutor = Interface::IQueryExecutor;

    //////////////////////////////////////////////////////////////////////

    class DataBase : public Interface::IDataBase
    {
       protected:
        DataBase(const std::string& newname) : m_name{newname}, m_tables{}
        {
        }

       public:
        static auto Create(const std::string& newname) -> UDataBase
        {
            Interface::UDataBase udb{new DataBase{newname}};
            return (udb);
        }

       public:
        auto Copy() const -> UDataBase override
        {
            return Copy(m_name);
        }

        auto Copy(const std::string& newname) const -> UDataBase override
        {
            auto newtable = Create(newname);
            for (auto&& table : m_tables)
            {
                newtable->AddTable(table->Copy(table->GetName()));
            }
            return newtable;
        }

        //////////////////////////////////////////////////////////////////

        auto GetName() const -> const std::string& override
        {
            return m_name;
        }
        void SetName(const std::string& name) override
        {
            Utility::Assert(name.size(), "database.cpp, name is empty");
            m_name = name;
        }

        //////////////////////////////////////////////////////////////////

       public:
        void AddTable(UTable table) override
        {
            AssertTableNotExists(table->GetName(), " AddTable:");
            m_tables.push_back(std::move(table));
        }
        void RemoveTable(const std::string& tbname) override
        {
            auto end = m_tables.end();
            auto result =
                std::remove_if(m_tables.begin(), end,
                               [tbname](const Interface::UTable& table)
                               {
                                   return table->GetName() == tbname;
                               });
            m_tables.erase(result, end);
            Utility::Assert(result != end,
                            " RemoveTable: table does not exist");
        }
        void RenameTable(const std::string& oldtbname,
                         const std::string& newtbname) override
        {
            auto&& table = GetTable(oldtbname);
            table.SetName(newtbname);
        }

        //////////////////////////////////////////////////////////////////

       public:
        auto TablesCount() const -> const int override
        {
            return static_cast<int>(m_tables.size());
        }

        auto ListTables() const -> UTableNameList override
        {
            UTableNameList ulist = std::make_unique<Interface::TableNameList>();
            for (auto&& table : m_tables)
            {
                ulist->push_back(table->GetName());
            }
            return ulist;
        }

        auto IsTableExists(const std::string& tbname) const -> bool override
        {
            auto&& result = GetTableIndex(tbname);
            return result != std::nullopt;
        }
        //////////////////////////////////////////////////////////////////

       public:
        auto GetTable(const std::string& tbname) const -> const ITable& override
        {
            return (GetTable(GetTableIndexAssert(
                tbname,
                fmt::format("GetTable(table-name: {}) const", tbname))));
        }
        auto GetTable(const std::string& tbname) -> ITable& override
        {
            return (GetTable(GetTableIndexAssert(
                tbname,
                fmt::format("GetTable(table-name: {}) const", tbname))));
        }

        //////////////////////////////////////////////////////////////////

       protected:
        void AssertTableNotExists(const std::string& tbname,
                                  const std::string& message) const
        {
            auto&& result = GetTableIndex(tbname);
            Utility::Assert(result == std::nullopt,
                            message + "  AssertTableNotExists: table exist");
        }

        void AssertTableExists(const std::string& tbname,
                               const std::string& message) const
        {
            auto&& result = GetTableIndex(tbname);
            Utility::Assert(
                result != std::nullopt,
                message + "  AssertTableExists: table does not exist");
        }

        //////////////////////////////////////////////////////////////////

       protected:
        auto GetTableIndex(const std::string& tbname) const
            -> const std::optional<int>
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
            return std::make_optional<int>(
                static_cast<int>(std::distance(begin, itr)));
        }

        auto GetTableIndexAssert(const std::string& tbname,
                                 const std::string& message) const -> const int
        {
            auto&& result = GetTableIndex(tbname);
            Utility::Assert(result != std::nullopt,
                            message +
                                " GetTableIndexAssert: table does not "
                                "exist");
            return *result;
        }

       protected:
        auto GetTable(const int index) const -> const ITable&
        {
            return *m_tables.at(index);
        }
        auto GetTable(const int index) -> ITable&
        {
            return *m_tables.at(index);
        }

        //////////////////////////////////////////////////////////////////

       protected:
        std::string m_name;
        TableList m_tables;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDataBase(const std::string& name) -> Interface::UDataBase
    {
        return DataBase::Create(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
