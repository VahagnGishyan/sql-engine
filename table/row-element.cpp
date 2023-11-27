
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

    auto RowElement::Copy() const -> Interface::UDynamicObject
    {
        Interface::URowElement obj{};
        obj->SetValue(*this);
        return obj;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowElement::GetType() const -> const Interface::DynamicType&
    {
        return m_dynobj.GetType();
    }

    void RowElement::SetType(const Interface::DynamicType& type)
    {
        m_dynobj.SetType(type);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void RowElement::SetValue(const IDynamicObject& obj)
    {
        m_dynobj.SetValue(obj);
    }
    void RowElement::SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value)
    {
        m_dynobj.SetValueAsInt(value);
    }
    void RowElement::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
    {
        m_dynobj.SetValueAsDouble(value);
    }
    void RowElement::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
    {
        m_dynobj.SetValueAsString(value);
    }

    auto RowElement::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
    {
        return m_dynobj.GetValueAsInt();
    }
    auto RowElement::GetValueAsDouble() const -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
    {
        return m_dynobj.GetValueAsDouble();
    }
    auto RowElement::GetValueAsString() const -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
    {
        return m_dynobj.GetValueAsString();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void RowElement::AssertTypeIs(const Interface::DynamicType& type) const
    {
        m_dynobj.AssertTypeIs(type);
    }
    void RowElement::AssertTypeIsNot(const Interface::DynamicType& type) const
    {
        m_dynobj.AssertTypeIsNot(type);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool RowElement::Equal(const IDynamicObject& rhs)
    {
        return m_dynobj.Equal(rhs);
    }

    bool RowElement::NotEqual(const IDynamicObject& element)
    {
        return m_dynobj.NotEqual(element);
    }

    bool RowElement::GreaterThan(const IDynamicObject& rhs)
    {
        return m_dynobj.GreaterThan(rhs);
    }
    bool RowElement::LessThan(const IDynamicObject& rhs)
    {
        return m_dynobj.LessThan(rhs);
    }
    bool RowElement::GreaterThanOrEqualTo(const IDynamicObject& rhs)
    {
        return m_dynobj.GreaterThanOrEqualTo(rhs);
    }
    bool RowElement::LessThanOrEqualTo(const IDynamicObject& rhs)
    {
        return m_dynobj.LessThanOrEqualTo(rhs);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
