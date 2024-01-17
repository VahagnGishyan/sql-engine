
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-object.hpp"
#include "i-row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IRow;

    using URow    = std::unique_ptr<IRow>;
    using ShRow   = std::shared_ptr<IRow>;
    using RowList = std::vector<URow>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IRow : public IDBObject
    {
    //    public:
    //     using ColumnList   = std::vector<std::string>;
    //     using ShColumnList = std::shared_ptr<ColumnList>;

    //    public:
    //     virtual auto Copy() const -> URow = 0;

    //    public:
    //     virtual auto CreateTable(const std::string& tablename) const
    //         -> UTable = 0;

    //    public:
    //     virtual auto GetTableName() const -> const std::string   = 0;
    //     virtual auto GetColumnList() const -> const ShColumnList = 0;

    //    public:
    //     virtual auto GetRowIndex() const -> const unsigned int = 0;
    //     virtual void SetRowIndex(const unsigned int rowindex)  = 0;

    //    public:
    //     virtual void AddElement(URowElement element) = 0;
    //     virtual auto GetElement(const int& index)
    //         -> Interface::IRowElement& = 0;
    //     virtual auto GetElement(const int& index) const
    //         -> const Interface::IRowElement& = 0;
    };

    //////////////////////////////////////////////////////////////////////

    template <typename T, typename... Types>
    PROJECT_SHARED_EXPORT auto MakeRow(Types&&... args) -> URow
    {
        static_assert(std::is_base_of<IRow, T>());
        return std::make_unique<T>(args...);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
