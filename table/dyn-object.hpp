
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// #include "interface/i-table.hpp"
#include <string>
#include <variant>

#include "interface/i-dyn-object.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DynamicValue : public Interface::IDynamicValue
    {
       protected:
        using DynamicValueType = std::variant<Interface::GetDynamicType<Interface::DynamicType::Int>::type,
                                              Interface::GetDynamicType<Interface::DynamicType::Double>::type,
                                              Interface::GetDynamicType<Interface::DynamicType::String>::type>;

       public:
        auto Copy() const -> Interface::UDynamicValue override;

       public:
        void SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value) override;
        void SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value) override;
        void SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value) override;

       public:
        auto GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicType<Interface::DynamicType::String>::type& override;

       public:
        bool Equal(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool NotEqual(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool GreaterThan(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool LessThan(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool GreaterThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool LessThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type) override;

       protected:
        DynamicValueType m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DynamicObject : public Interface::IDynamicObject
    {
       public:
        auto Copy() const -> Interface::UDynamicObject override;
        auto CopyValue() const -> Interface::UDynamicValue override;

       public:
        void SetType(const Interface::DynamicType& type) override;
        auto GetType() const -> const Interface::DynamicType& override;

       public:
        void SetValue(const IDynamicObject& obj) override;
        void SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value) override;
        void SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value) override;
        void SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value) override;

       public:
        auto GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicType<Interface::DynamicType::String>::type& override;

        void AssertTypeIs(const Interface::DynamicType& type) const;
        void AssertTypeIsNot(const Interface::DynamicType& type) const;

       public:
        bool Equal(const IDynamicObject& element) override;
        bool NotEqual(const IDynamicObject& element) override;
        bool GreaterThan(const IDynamicObject& element) override;
        bool LessThan(const IDynamicObject& element) override;
        bool GreaterThanOrEqualTo(const IDynamicObject& element) override;
        bool LessThanOrEqualTo(const IDynamicObject& element) override;

       public:
        template <Interface::DynamicType DynType>
        void SetValue(const typename Interface::GetDynamicType<DynType>::type& value)
        {
            SetType(DynType);
            m_value = value;
        }
        template <Interface::DynamicType DynType>
        auto GetValue() const -> typename Interface::GetDynamicType<DynType>::type
        {
            return std::get<typename Interface::GetDynamicType<DynType>::type>(m_value);
        }

       protected:
        Interface::DynamicType m_type = Interface::DynamicType::Unset;
        DynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
