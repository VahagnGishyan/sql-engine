
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "dyn-object.hpp"

#include <fmt/core.h>

#include <stdexcept>

#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DynamicObject::GetType() const -> const Interface::DynamicObjectType&
    {
        return m_type;
    }

    void DynamicObject::SetType(const Interface::DynamicObjectType& type)
    {
        m_type = type;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DynamicObject::SetValueAsInt(
        const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type& value)
    {
        m_value = value;
    }
    void DynamicObject::SetValueAsDouble(
        const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type& value)
    {
        m_value = value;
    }
    void DynamicObject::SetValueAsString(
        const Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type& value)
    {
        m_value = value;
    }

    auto DynamicObject::GetValueAsInt() const
        -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type&
    {
        return std::get<Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type>(m_value);
    }
    auto DynamicObject::GetValueAsDouble() const
        -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type&
    {
        return std::get<Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type>(m_value);
    }
    auto DynamicObject::GetValueAsString() const
        -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type&
    {
        return std::get<Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type>(m_value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void DynamicObject::AssertTypeIs(const Interface::DynamicObjectType& type) const
    {
        Utility::Assert(GetType() == type,
                        fmt::format("DynamicObject::AssertTypeIs(type: {}), types are different, this->type: {}",
                                    Interface::GetDynamicObjectTypeNameAsString(type),
                                    Interface::GetDynamicObjectTypeNameAsString(m_type)));
    }
    void DynamicObject::AssertTypeIsNot(const Interface::DynamicObjectType& type) const
    {
        Utility::Assert(GetType() != type, fmt::format("DynamicObject::AssertTypeIsNot(type: {}), types are the same",
                                                       Interface::GetDynamicObjectTypeNameAsString(type)));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool DynamicObject::Equal(const IDynamicObject& rhs)
    {
        AssertTypeIsNot(Interface::DynamicObjectType::Double);
        AssertTypeIs(rhs.GetType());

        if (GetType() == Interface::DynamicObjectType::String)
        {
            return this->GetValueAsString() == rhs.GetValueAsString();
        }

        if (GetType() == Interface::DynamicObjectType::Int)
        {
            return this->GetValueAsInt() == rhs.GetValueAsInt();
        }

        Utility::Assert(false, fmt::format("DynamicObject::Equal(rhs.type: {}) this->type: {}, invalid types",
                                           GetDynamicObjectTypeNameAsString(rhs.GetType()),
                                           GetDynamicObjectTypeNameAsString(GetType())));
        return false;
    }

    bool DynamicObject::NotEqual(const IDynamicObject& element)
    {
        return (Equal(element) == false);
    }

    bool DynamicObject::GreaterThan(const IDynamicObject& rhs)
    {
        AssertTypeIsNot(Interface::DynamicObjectType::String);
        AssertTypeIs(rhs.GetType());

        if (GetType() == Interface::DynamicObjectType::Int)
        {
            return this->GetValueAsInt() > rhs.GetValueAsInt();
        }

        if (GetType() == Interface::DynamicObjectType::Double)
        {
            return this->GetValueAsDouble() > rhs.GetValueAsDouble();
        }

        Utility::Assert(false, fmt::format("DynamicObject::GreaterThan(rhs.type: {}) this->type: {}, invalid types",
                                           GetDynamicObjectTypeNameAsString(rhs.GetType()),
                                           GetDynamicObjectTypeNameAsString(GetType())));
        return false;
    }
    bool DynamicObject::LessThan(const IDynamicObject& rhs)
    {
        return ((NotEqual(rhs)) && (!GreaterThan(rhs)));
    }
    bool DynamicObject::GreaterThanOrEqualTo(const IDynamicObject& rhs)
    {
        return (!LessThan(rhs));
    }
    bool DynamicObject::LessThanOrEqualTo(const IDynamicObject& rhs)
    {
        return (!GreaterThan(rhs));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
