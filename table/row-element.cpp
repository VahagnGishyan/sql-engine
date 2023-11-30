
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowElement::Copy() const -> Interface::URowElement
    {
        auto&& obj     = std::make_unique<RowElement>();
        obj->m_pobject = CopyObject();
        return std::move(obj);
    }

    auto RowElement::CopyObject() const -> Interface::UDynamicObject
    {
        return (m_pobject->CopyObject());
    }

    auto RowElement::CopyValue() const -> Interface::UDynamicValue
    {
        return (m_pobject->CopyValue());
    }

    auto RowElement::IsNull() const -> bool
    {
        return (m_pobject == nullptr || m_pobject->IsNull());
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowElement::GetType() const -> const Interface::DynamicType&
    {
        return m_pobject->GetType();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void RowElement::SetValue(const IDynamicObject& obj)
    {
        m_pobject->SetValue(obj);
    }
    void RowElement::SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value)
    {
        m_pobject->SetValueAsInt(value);
    }
    void RowElement::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
    {
        m_pobject->SetValueAsDouble(value);
    }
    void RowElement::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
    {
        m_pobject->SetValueAsString(value);
    }

    auto RowElement::GetValue() const -> const Interface::IDynamicValue&
    {
        return m_pobject->GetValue();
    }

    auto RowElement::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
    {
        return m_pobject->GetValueAsInt();
    }
    auto RowElement::GetValueAsDouble() const -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
    {
        return m_pobject->GetValueAsDouble();
    }
    auto RowElement::GetValueAsString() const -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
    {
        return m_pobject->GetValueAsString();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void RowElement::AssertTypeIs(const Interface::DynamicType& type) const
    {
        m_pobject->AssertTypeIs(type);
    }
    void RowElement::AssertTypeIsNot(const Interface::DynamicType& type) const
    {
        m_pobject->AssertTypeIsNot(type);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool RowElement::Equal(const IDynamicObject& rhs)
    {
        return m_pobject->Equal(rhs);
    }

    bool RowElement::NotEqual(const IDynamicObject& element)
    {
        return m_pobject->NotEqual(element);
    }

    bool RowElement::GreaterThan(const IDynamicObject& rhs)
    {
        return m_pobject->GreaterThan(rhs);
    }
    bool RowElement::LessThan(const IDynamicObject& rhs)
    {
        return m_pobject->LessThan(rhs);
    }
    bool RowElement::GreaterThanOrEqualTo(const IDynamicObject& rhs)
    {
        return m_pobject->GreaterThanOrEqualTo(rhs);
    }
    bool RowElement::LessThanOrEqualTo(const IDynamicObject& rhs)
    {
        return m_pobject->LessThanOrEqualTo(rhs);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
