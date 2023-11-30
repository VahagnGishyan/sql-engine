
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
        using DynamicValueType  = std::variant<Interface::GetDynamicType<Interface::DynamicType::Int>::type,
                                              Interface::GetDynamicType<Interface::DynamicType::Double>::type,
                                              Interface::GetDynamicType<Interface::DynamicType::String>::type>;
        using UDynamicValueType = std::unique_ptr<DynamicValueType>;

       protected:
        virtual void Init();

       public:
        auto CopyValue() const -> Interface::UDynamicValue override;
        auto IsNull() const -> bool override;

       protected:
        virtual void AssertIsNull() const;
        virtual void AssertIsNotNull() const;

       protected:
        virtual void SetValue(const DynamicValue& obj);

       public:
        void SetValue(const IDynamicValue& obj, const Interface::DynamicType& type) override;
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
        UDynamicValueType m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DynamicObject : public Interface::IDynamicObject
    {
       public:
        auto CopyObject() const -> Interface::UDynamicObject override;
        auto CopyValue() const -> Interface::UDynamicValue override;
        auto IsNull() const -> bool override;

       protected:
        virtual void SetType(const Interface::DynamicType& type);

       public:
        auto GetType() const -> const Interface::DynamicType& override;

       public:
        void SetValue(const IDynamicObject& obj) override;
        void SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value) override;
        void SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value) override;
        void SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value) override;

       public:
        auto GetValue() const -> const Interface::IDynamicValue& override;
        auto GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicType<Interface::DynamicType::String>::type& override;

       public:
        void AssertTypeIs(const Interface::DynamicType& type) const override;
        void AssertTypeIsNot(const Interface::DynamicType& type) const override;

       public:
        bool Equal(const IDynamicObject& element) override;
        bool NotEqual(const IDynamicObject& element) override;
        bool GreaterThan(const IDynamicObject& element) override;
        bool LessThan(const IDynamicObject& element) override;
        bool GreaterThanOrEqualTo(const IDynamicObject& element) override;
        bool LessThanOrEqualTo(const IDynamicObject& element) override;

       protected:
        Interface::DynamicType m_type = Interface::DynamicType::Unset;
        Interface::UDynamicValue m_pValue;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
