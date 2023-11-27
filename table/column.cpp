
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column.hpp"

#include "column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // void Column::Init(const Interface::IColumnInit& init)
    // {
    // }

    // auto Column::Copy() const -> Interface::UColumn
    // {
    //     auto column    = std::make_unique<Column>();
    //     column->m_type = m_type;
    //     column->m_id   = m_id->Copy();
    //     for (auto&& element : m_elements)
    //     {
    //         column->AddElement(element->Copy());
    //     }
    //     return column;
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Column::GetID() const -> const Interface::IColumnID&
    {
        return *m_id;
    }
    auto Column::GetSize() const -> unsigned int
    {
        return m_elements.size();
    }
    auto Column::GetType() const -> const Interface::DynamicType
    {
        return m_type;
    }

    void Column::SetType(const Interface::DynamicType& type)
    {
        m_type = type;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::AddElement(Interface::UColumnElement element)
    {
        m_elements.push_back(std::move(element));
    }
    // auto Column::GetElement(const Interface::IColumnID& id) -> Interface::UColumnElement
    // {
    // }
    // auto Column::GetElementsIDs(std::function<bool(const Interface::IColumnElement&)> predicate)
    //     -> Interface::UColumnIDList
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // void Column::AddConstraint(Interface::UColumnConstraint constraint)
    // {
    // }
    // void Column::AddConstraints(Interface::UColumnConstraintList element)
    // {
    // }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Column::RemoveElementsIf(std::function<bool(const Interface::IColumnElement&)> predicate)
    {
        auto endIt = std::remove_if(m_elements.begin(), m_elements.end(),
                                    [&predicate](const Interface::UColumnElement& ptritem)
                                    {
                                        return predicate(*ptritem);
                                    });
        // Remove all even numbers collected in the end of vector
        m_elements.erase(endIt, m_elements.end());
    }
    void Column::UpdateElementsIf(std::function<void(Interface::IColumnElement&)> modifier)
    {
        std::for_each(m_elements.begin(), m_elements.end(),
                      [&modifier](Interface::UColumnElement& ptritem)
                      {
                          modifier(*ptritem);
                      });
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
