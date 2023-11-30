
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

    void DynamicValue::Init()
    {
        AssertIsNull();
        m_value = std::make_unique<DynamicValueType>();
    }

    auto DynamicValue::CopyValue() const -> Interface::UDynamicValue
    {
        auto&& obj = std::make_unique<DynamicValue>();
        obj->SetValue(*this);
        return std::move(obj);
    }

    auto DynamicValue::IsNull() const -> bool
    {
        return (m_value == nullptr);
    }

    void DynamicValue::AssertIsNull() const
    {
        if (m_value != nullptr)
        {
            throw std::logic_error{"DynamicValue::AssertIsNull(), value is not null"};
        }
    }

    void DynamicValue::AssertIsNotNull() const
    {
        if (m_value == nullptr)
        {
            throw std::logic_error{"DynamicValue::AssertIsNull(), value is null"};
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DynamicValue::SetValue(const DynamicValue& obj)
    {
        if (m_value == nullptr)
        {
            Init();
        }
        *m_value = *obj.m_value;
    }

    void DynamicValue::SetValue(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        if (m_value == nullptr)
        {
            Init();
        }
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
        if (m_value == nullptr)
        {
            Init();
        }
        *m_value = value;
    }
    void DynamicValue::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
    {
        if (m_value == nullptr)
        {
            Init();
        }
        *m_value = value;
    }
    void DynamicValue::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
    {
        if (m_value == nullptr)
        {
            Init();
        }
        *m_value = value;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DynamicValue::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
    {
        AssertIsNotNull();
        return std::get<Interface::GetDynamicType<Interface::DynamicType::Int>::type>(*m_value);
    }
    auto DynamicValue::GetValueAsDouble() const
        -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
    {
        AssertIsNotNull();
        return std::get<Interface::GetDynamicType<Interface::DynamicType::Double>::type>(*m_value);
    }
    auto DynamicValue::GetValueAsString() const
        -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
    {
        AssertIsNotNull();
        return std::get<Interface::GetDynamicType<Interface::DynamicType::String>::type>(*m_value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool DynamicValue::Equal(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        AssertIsNotNull();
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
        AssertIsNotNull();
        return (Equal(value, type) == false);
    }
    bool DynamicValue::GreaterThan(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        AssertIsNotNull();
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
        AssertIsNotNull();
        return ((NotEqual(value, type)) && (!GreaterThan(value, type)));
    }
    bool DynamicValue::GreaterThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        AssertIsNotNull();
        return (!LessThan(value, type));
    }
    bool DynamicValue::LessThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type)
    {
        AssertIsNotNull();
        return (!GreaterThan(value, type));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
