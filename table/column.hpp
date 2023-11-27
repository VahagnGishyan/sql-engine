
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

#include "interface/i-column.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Column : public Interface::IColumn
    {
       protected:
        using ColumnElementList = std::vector<Interface::UColumnElement>;

       public:
        // void Init(const Interface::IColumnInit& init) override;
        // auto Copy() const -> Interface::UColumn override;

       public:
        auto GetID() const -> const Interface::IColumnID& override;
        auto GetSize() const -> unsigned int override;
        auto GetType() const -> const Interface::DynamicType override;
        void SetType(const Interface::DynamicType& type) override;

       public:
        void AddElement(Interface::UColumnElement element) override;
        // auto GetElement(const Interface::IColumnID& id) -> Interface::UColumnElement override;
        // auto GetElementsIDs(std::function<bool(const Interface::IColumnElement&)> predicate)
        //     -> Interface::UColumnIDList override;

    //    public:
    //     void AddConstraint(Interface::UColumnConstraint constraint) override;
    //     void AddConstraints(Interface::UColumnConstraintList element) override;

       public:
        void RemoveElementsIf(std::function<bool(const Interface::IColumnElement&)> predicate) override;
        void UpdateElementsIf(std::function<void(Interface::IColumnElement&)> modifier) override;

       protected:
        Interface::DynamicType m_type;
        ColumnElementList m_elements;
        Interface::UColumnID m_id;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
