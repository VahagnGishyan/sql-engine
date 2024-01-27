
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <functional>

#include "i-db-object.hpp"
#include "i-dynamic-types.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IColumn;

    using UColumn    = std::unique_ptr<IColumn>;
    using ShColumn   = std::shared_ptr<IColumn>;
    using ColumnList = std::vector<UColumn>;

    using ColumnElementList = std::vector<std::unique_ptr<DynamicValue>>;

    using ColumnNameList   = std::vector<std::string>;
    using UColumnNameList  = std::unique_ptr<ColumnNameList>;
    using ShColumnNameList = std::shared_ptr<ColumnNameList>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IColumn : public IDBObject
    {
       public:
        virtual auto Copy() const -> UColumn                           = 0;
        virtual auto Copy(const std::string& newname) const -> UColumn = 0;

       public:
        virtual auto GetName() const -> const std::string& = 0;
        virtual void SetName(const std::string& name)      = 0;
        virtual auto GetSize() const -> int       = 0;

       public:
        virtual void SetType(const DynamicType& type)     = 0;
        virtual auto GetType() const -> const DynamicType = 0;

       public:
        virtual void AddElement(UDynamicValue element)              = 0;
        virtual auto GetElement(const int& index) -> UDynamicValue& = 0;
        virtual auto GetElement(const int& index) const
            -> const UDynamicValue& = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
