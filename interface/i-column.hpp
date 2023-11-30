
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
        virtual auto GetID() const -> const IColumnID&    = 0;
        virtual auto GetSize() const -> unsigned int      = 0;
        virtual auto GetType() const -> const DynamicType = 0;

       public:
        virtual void SetType(const DynamicType& type) = 0;

       public:
        virtual void AddElement(UColumnElement element)                                           = 0;
        virtual auto At(const int index) -> Interface::IColumnElement&                            = 0;
        virtual auto GetElement(const int& index) -> Interface::UColumnElement                    = 0;
        virtual auto GetElements(const std::vector<int> indexes) -> Interface::UColumnElementList = 0;

       public:
        virtual void AddConstraint(UColumnConstraint constraint)   = 0;
        virtual void AddConstraints(UColumnConstraintList element) = 0;

       public:
        virtual void ForEach(const std::function<void(const IColumnElement&)> predicate) const    = 0;
        virtual void RemoveElements(const std::vector<int> indexes)                               = 0;
        virtual void RemoveElementsIf(const std::function<bool(const IColumnElement&)> predicate) = 0;
        virtual void UpdateElementsIf(const std::function<void(IColumnElement&)> modifier)        = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
