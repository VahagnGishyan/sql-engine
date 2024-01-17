
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::TableNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    RowElement::RowElement(const unsigned int columnIndex,
                           const DynamicValue& value) :
        m_columnIndex{columnIndex}, m_value{value}
    {
    }

    //////////////////////////////////////////////////////////////////////

    auto RowElement::Create(const unsigned int columnIndex,
                            const DynamicValue& value) -> Interface::URowElement
    {
        auto urow =
            std::unique_ptr<RowElement>(new RowElement{columnIndex, value});
        return urow;
    }

    auto RowElement::Create(const IRowElement& element)
        -> Interface::URowElement
    {
        return Create(element.GetColumnIndex(), element.GetValue());
    }

    //////////////////////////////////////////////////////////////////////

    auto RowElement::Copy() const -> Interface::URowElement
    {
        return Create(*this);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto RowElement::GetColumnIndex() const -> const unsigned int
    {
        return (m_columnIndex);
    }

    void RowElement::SetColumnIndex(const unsigned int columnIndex)
    {
        m_columnIndex = columnIndex;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void RowElement::SetValue(const DynamicValue& value)
    {
        m_value = value;
    }
    void RowElement::SetValue(const IRowElement& element)
    {
        SetValue(element.GetValue());
    }
    auto RowElement::GetValue() -> DynamicValue&
    {
        return m_value;
    }
    auto RowElement::GetValue() const -> const DynamicValue&
    {
        return m_value;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool RowElement::Equal(const DynamicValue& value) const
    {
        return m_value == value;
    }
    bool RowElement::Equal(const IRowElement& element) const
    {
        return Equal(element.GetValue());
    }

    bool RowElement::NotEqual(const DynamicValue& value) const
    {
        return !Equal(value);
    }
    bool RowElement::NotEqual(const IRowElement& element) const
    {
        return NotEqual(element.GetValue());
    }

    bool RowElement::GreaterThan(const DynamicValue& value) const
    {
        return m_value > value;
    }
    bool RowElement::GreaterThan(const IRowElement& element) const
    {
        return GreaterThan(element.GetValue());
    }

    bool RowElement::LessThan(const DynamicValue& value) const
    {
        return (NotEqual(value) && !GreaterThan(value));
    }
    bool RowElement::LessThan(const IRowElement& element) const
    {
        return LessThan(element.GetValue());
    }

    bool RowElement::GreaterThanOrEqualTo(const DynamicValue& value) const
    {
        return (!LessThan(value));
    }
    bool RowElement::GreaterThanOrEqualTo(const IRowElement& element) const
    {
        return GreaterThanOrEqualTo(element.GetValue());
    }

    bool RowElement::LessThanOrEqualTo(const DynamicValue& value) const
    {
        return (!GreaterThan(value));
    }
    bool RowElement::LessThanOrEqualTo(const IRowElement& element) const
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
