
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <functional>

#include "i-column-comps.hpp"

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

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IColumn : public IDBObject
    {
       public:
        virtual void Init(const IColumnInit& init) = 0;
        virtual auto Copy() const -> UColumn       = 0;

       public:
        virtual auto GetID() const -> const IColumnID& = 0;
        virtual auto GetSize() const -> unsigned int;
        virtual auto GetType() const -> const DynamicType;

       public:
        virtual void SetType(const DynamicType& type) = 0;

       public:
        virtual void AddElement(UColumnElement element)                                                    = 0;
        virtual auto GetElement(const IColumnID& id) -> IColumnElement                                     = 0;
        virtual auto GetElementsIDs(std::function<bool(const IColumnElement&)> predicate) -> UColumnIDList = 0;

       public:
        virtual void AddConstraint(UColumnConstraint constraint)   = 0;
        virtual void AddConstraints(UColumnConstraintList element) = 0;

       public:
        virtual auto RemoveElementsIf(std::function<bool(const IColumnElement&)> predicate) -> UColumnIDList = 0;
        virtual auto UpdateElementsIf(std::function<bool(const IColumnElement&)> predicate,
                                      std::function<void(IColumnElement&)> modifier) -> UColumnIDList        = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
