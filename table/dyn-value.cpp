
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <stdexcept>

#include "dyn-object.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DynamicValue::CopyValue() const -> Interface::UDynamicValue
    {
        auto&& obj   = std::make_unique<DynamicValue>();
        obj->m_value = m_value;
        return std::move(obj);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DynamicValue::SetValue(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        if (type == Interface::DynamicType::Int)
        {
            SetValueAsInt(value.GetValueAsInt());
            return;
        }
        if (type == Interface::DynamicType::Double)
        {
            SetValueAsDouble(value.GetValueAsDouble());
            return;
        }
        if (type == Interface::DynamicType::String)
        {
            SetValueAsString(value.GetValueAsString());
            return;
        }
        Utility::Assert(false,
                        fmt::format("dyn-value.cpp, DynamicValue::SetValue(value, type), type: {} is unsupported",
                                    Interface::GetDynamicTypeNameAsString(type)));
    }

    void DynamicValue::SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value)
    {
        m_value = value;
    }
    void DynamicValue::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
    {
        m_value = value;
    }
    void DynamicValue::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
    {
        m_value = value;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DynamicValue::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
    {
        return std::get<Interface::GetDynamicType<Interface::DynamicType::Int>::type>(m_value);
    }
    auto DynamicValue::GetValueAsDouble() const
        -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
    {
        return std::get<Interface::GetDynamicType<Interface::DynamicType::Double>::type>(m_value);
    }
    auto DynamicValue::GetValueAsString() const
        -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
    {
        return std::get<Interface::GetDynamicType<Interface::DynamicType::String>::type>(m_value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool DynamicValue::Equal(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        if (type == Interface::DynamicType::Int)
        {
            return GetValueAsInt() == value.GetValueAsInt();
        }
        if (type == Interface::DynamicType::Double)
        {
            return GetValueAsDouble() == value.GetValueAsDouble();
        }
        if (type == Interface::DynamicType::String)
        {
            return GetValueAsString() == value.GetValueAsString();
        }
        Utility::Assert(
            false, fmt::format("table::dyn-value.cpp, DynamicValue::Equal(value, type), value-type: {} is unsupported",
                               Interface::GetDynamicTypeNameAsString(type)));
        return false;
    }
    bool DynamicValue::NotEqual(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return (Equal(value, type) == false);
    }
    bool DynamicValue::GreaterThan(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        if (type == Interface::DynamicType::Int)
        {
            return GetValueAsInt() > value.GetValueAsInt();
        }
        if (type == Interface::DynamicType::Double)
        {
            return GetValueAsDouble() > value.GetValueAsDouble();
        }
        if (type == Interface::DynamicType::String)
        {
            return GetValueAsString() > value.GetValueAsString();
        }
        Utility::Assert(
            false,
            fmt::format("table::dyn-value.cpp, DynamicValue::GreaterThan(value, type), value-type: {} is unsupported",
                        Interface::GetDynamicTypeNameAsString(type)));
        return false;
    }
    bool DynamicValue::LessThan(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return ((NotEqual(value, type)) && (!GreaterThan(value, type)));
    }
    bool DynamicValue::GreaterThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return (!LessThan(value, type));
    }
    bool DynamicValue::LessThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        return (!GreaterThan(value, type));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
