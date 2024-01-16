
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column.hpp"

#include "column-element.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::TableNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    Column::Column(const std::string& name,
                   const Interface::DynamicType& type) :
        m_name{name}, m_type{type}, m_elements{}
    // , m_constraintList{nullptr}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Column::Create(const std::string& name,
                        const Interface::DynamicType& type)
        -> Interface::UColumn
    {
        Interface::UColumn ucolumn{
            new Column{name, type}
        };
        return (ucolumn);
    }

    auto Column::Copy(const std::string& newname) const -> Interface::UColumn
    {
        auto&& newcolumn = Column::Create(newname, m_type);
        for (auto&& item : m_elements)
        {
            newcolumn->AddElement(item->Copy());
        }
        return std::move(newcolumn);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Column::GetName() const -> const std::string&
    {
        return m_name;
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

    auto Column::At(const int index) -> Interface::IColumnElement&
    {
        return *m_elements.at(index);
    }

    auto Column::GetElement(const int& index) -> Interface::IColumnElement&
    {
        return *m_elements.at(index);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::TableNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
