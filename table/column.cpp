
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column.hpp"

#include "column-element.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    Column::Column() :
        m_type{Interface::DynamicType::Unset}, m_elements{}, m_id{nullptr}
    // , m_constraintList{nullptr}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Column::Create(const Interface::IColumnInit& init)
        -> Interface::UColumn
    {
        Column obj{};
        Interface::UColumn ucolumn{new Column{}};
        ucolumn->Init(init);
        return (ucolumn);
    }

    void Column::Init(const Interface::IColumnInit& initializer)
    {
        AssertNotInitialized("Column::Init(), ");
        m_type     = initializer.GetType();
        m_id       = initializer.GetID();
        m_elements = initializer.GetElements();
        // m_constraintList;
    }

    auto Column::Copy() const -> Interface::UColumn
    {
        Interface::NotImplYet("Column::AddConstraint");
        return nullptr;  // for compiler

        // AssertInitialized ?

        // auto column    = std::make_unique<Column>();
        // column->m_type = m_type;
        // column->m_id   = m_id->Copy();
        // for (auto&& element : m_elements)
        // {
        //     column->AddElement(element->Copy());
        // }
        // return column;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Column::GetID() const -> const Interface::IColumnID&
    {
        AssertInitialized("Column::GetID, ");
        return *m_id;
    }
    // auto Column::GetInfo() const -> const Interface::UDBObjectInfo
    // {
    //     AssertInitialized("Column::GetID, ");
    //     return *m_id;
    // }
    auto Column::GetSize() const -> unsigned int
    {
        AssertInitialized("Column::GetSize, ");
        return m_elements->size();
    }
    auto Column::GetType() const -> const Interface::DynamicType
    {
        AssertInitialized("Column::GetType, ");
        return m_type;
    }

    void Column::SetType(const Interface::DynamicType& type)
    {
        AssertInitialized("Column::SetType, ");
        m_type = type;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::AddElement(Interface::UColumnElement element)
    {
        AssertInitialized("Column::AddElement, ");
        m_elements->push_back(std::move(element));
    }

    auto Column::At(const int index) -> Interface::IColumnElement&
    {
        AssertInitialized("Column::At, ");
        return *m_elements->at(index);
    }

    auto Column::GetElement(const int& index) -> Interface::UColumnElement
    {
        AssertInitialized("Column::GetElement, ");
        return m_elements->at(index)->Copy();
    }

    auto Column::GetElements(const std::vector<int> indexes)
        -> Interface::UColumnElementList
    {
        AssertInitialized("Column::GetElement, ");
        auto list = std::make_unique<Interface::ColumnElementList>();
        std::for_each(m_elements->begin(), m_elements->end(),
                      [&list](const Interface::UColumnElement& element)
                      {
                          list->push_back(element->Copy());
                      });
        return list;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::AddConstraint(Interface::UColumnConstraint constraint)
    {
        Interface::NotImplYet("Column::AddConstraint");
        // AssertInitialized("Column::AddConstraint, ");
        // m_constraintList->push_back(std::move(constraint));
    }

    void Column::AddConstraints(Interface::UColumnConstraintList constraintList)
    {
        Interface::NotImplYet("Column::AddConstraints");
        // AssertInitialized("Column::AddConstraints, ");
        // for (auto&& element : *constraintList)
        // {
        //     m_constraintList->push_back(std::move(element));
        // }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::ForEach(
        const std::function<void(const Interface::IColumnElement&)> predicate)
        const
    {
        Interface::NotImplYet("Column::ForEach");
    }

    void Column::RemoveElements(const std::vector<int> indexes)
    {
        Interface::NotImplYet("Column::RemoveElements");
    }

    void Column::RemoveElementsIf(
        std::function<bool(const Interface::IColumnElement&)> predicate)
    {
        Interface::NotImplYet("Column::AddConstraints");
        // auto endIt = std::remove_if(m_elements.begin(), m_elements.end(),
        //                             [&predicate](const
        //                             Interface::UColumnElement& ptritem)
        //                             {
        //                                 return predicate(*ptritem);
        //                             });
        // // Remove all even numbers collected in the end of vector
        // m_elements.erase(endIt, m_elements.end());
    }
    void Column::UpdateElementsIf(
        std::function<void(Interface::IColumnElement&)> modifier)
    {
        Interface::NotImplYet("Column::AddConstraints");
        // std::for_each(m_elements.begin(), m_elements.end(),
        //               [&modifier](Interface::UColumnElement& ptritem)
        //               {
        //                   modifier(*ptritem);
        //               });
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::AssertInitialized(const std::string& message) const
    {
        Utility::Assert(m_id != nullptr,
                        message + "The column should have been initialized");
    }

    void Column::AssertNotInitialized(const std::string& message) const
    {
        Utility::Assert(m_id == nullptr,
                        message + "The column has already been initialized.");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
