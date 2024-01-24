
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

#include "interface/i-database.hpp"
#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT DataBase : public Interface::IDataBase
    {
       protected:
        using ITable         = Interface::ITable;
        using UTable         = Interface::UTable;
        using TableList      = Interface::TableList;
        using UTableNameList = Interface::UTableNameList;

        using IDataBase = Interface::IDataBase;
        using UDataBase = Interface::UDataBase;

        using IQuery = Interface::IQuery;

       protected:
        DataBase(const std::string& dbname);

       public:
        static auto Create(const std::string& newname) -> UDataBase;

       public:
        auto Copy(const std::string& dbname) const -> UDataBase override;
        auto Copy() const -> UDataBase override;

       public:
        auto GetName() const -> const std::string& override;
        void SetName(const std::string& name) override;

       public:
        void AddTable(UTable table) override;
        void RemoveTable(const std::string& tbname) override;
        void RenameTable(const std::string& oldname,
                         const std::string& newname) override;

       public:
        auto TablesCount() const -> const int override;
        auto ListTables() const -> UTableNameList override;
        auto IsTableExists(const std::string& tbname) const -> bool override;

       public:
        auto GetTable(const std::string& tbname) -> ITable& override;
        auto GetTable(const std::string& tbname) const
            -> const ITable& override;

       public:
        void Execute(const IQuery& query) override;

       protected:
        void AssertTableExists(const std::string& tbname,
                               const std::string& message) const;
        void AssertTableNotExists(const std::string& tbname,
                                  const std::string& message) const;

       protected:
        auto GetTableIndex(const std::string& tbname) const
            -> const std::optional<unsigned int>;
        auto GetTableIndexAssert(const std::string& tbname,
                                 const std::string& message) const -> const
            unsigned int;

       protected:
        auto GetTable(const int index) -> ITable&;
        auto GetTable(const int index) const -> const ITable&;

       protected:
        std::string m_name;
        TableList m_tables;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
