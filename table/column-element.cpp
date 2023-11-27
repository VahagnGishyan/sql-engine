
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ColumnElement::Copy() const -> Interface::UColumnElement
    {
        auto&& obj    = std::make_unique<ColumnElement>();
        obj->m_pValue = CopyValue();
        return std::move(obj);
    }

    auto ColumnElement::CopyValue() const -> Interface::UDynamicValue
    {
        return m_pValue->CopyValue();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void ColumnElement::SetValue(const IDynamicValue& obj, const Interface::DynamicType& type)
    {
        m_pValue->SetValue(obj, type);
    }
    void ColumnElement::SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value)
    {
        m_pValue->SetValueAsInt(value);
    }
    void ColumnElement::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
    {
        m_pValue->SetValueAsDouble(value);
    }
    void ColumnElement::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
    {
        m_pValue->SetValueAsString(value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ColumnElement::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
    {
        return m_pValue->GetValueAsInt();
    }
    auto ColumnElement::GetValueAsDouble() const
        -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
    {
        return m_pValue->GetValueAsDouble();
    }
    auto ColumnElement::GetValueAsString() const
        -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
    {
        return m_pValue->GetValueAsString();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool ColumnElement::Equal(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->Equal(value, type);
    }
    bool ColumnElement::NotEqual(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->NotEqual(value, type);
    }
    bool ColumnElement::GreaterThan(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->GreaterThan(value, type);
    }
    bool ColumnElement::LessThan(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->LessThan(value, type);
    }
    bool ColumnElement::GreaterThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->GreaterThanOrEqualTo(value, type);
    }
    bool ColumnElement::LessThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return m_pValue->LessThanOrEqualTo(value, type);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
