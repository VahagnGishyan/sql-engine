
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::TableNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    ColumnElement::ColumnElement(const DynamicValue& value) : m_value{value}
    {
    }

    //////////////////////////////////////////////////////////////////////

    auto ColumnElement::Create(const DynamicValue& value)
        -> Interface::UColumnElement
    {
        auto uelement =
            std::unique_ptr<ColumnElement>(new ColumnElement{value});
        return uelement;
    }

    auto ColumnElement::Create(const IColumnElement& element)
        -> Interface::UColumnElement
    {
        return Create(element.GetValue());
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ColumnElement::Copy() const -> Interface::UColumnElement
    {
        return Create(*this);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void ColumnElement::SetValue(const DynamicValue& value)
    {
        m_value = value;
    }
    void ColumnElement::SetValue(const IColumnElement& element)
    {
        SetValue(element.GetValue());
    }
    auto ColumnElement::GetValue() -> DynamicValue&
    {
        return m_value;
    }
    auto ColumnElement::GetValue() const -> const DynamicValue&
    {
        return m_value;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool ColumnElement::Equal(const DynamicValue& value) const
    {
        return m_value == value;
    }
    bool ColumnElement::Equal(const IColumnElement& element) const
    {
        return Equal(element.GetValue());
    }

    bool ColumnElement::NotEqual(const DynamicValue& value) const
    {
        return !Equal(value);
    }
    bool ColumnElement::NotEqual(const IColumnElement& element) const
    {
        return NotEqual(element.GetValue());
    }

    bool ColumnElement::GreaterThan(const DynamicValue& value) const
    {
        return m_value > value;
    }
    bool ColumnElement::GreaterThan(const IColumnElement& element) const
    {
        return GreaterThan(element.GetValue());
    }

    bool ColumnElement::LessThan(const DynamicValue& value) const
    {
        return (NotEqual(value) && !GreaterThan(value));
    }
    bool ColumnElement::LessThan(const IColumnElement& element) const
    {
        return LessThan(element.GetValue());
    }

    bool ColumnElement::GreaterThanOrEqualTo(const DynamicValue& value) const
    {
        return (!LessThan(value));
    }
    bool ColumnElement::GreaterThanOrEqualTo(
        const IColumnElement& element) const
    {
        return GreaterThanOrEqualTo(element.GetValue());
    }

    bool ColumnElement::LessThanOrEqualTo(const DynamicValue& value) const
    {
        return (!GreaterThan(value));
    }
    bool ColumnElement::LessThanOrEqualTo(const IColumnElement& element) const
    {
        return LessThanOrEqualTo(element.GetValue());
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::TableNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
