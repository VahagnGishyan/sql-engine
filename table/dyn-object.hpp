
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

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DynamicObject : Interface::IDynamicObject
    {
       protected:
        using DynamicValue = std::variant<Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type,
                                          Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type,
                                          Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type>;

       public:
        void SetType(const Interface::DynamicObjectType& type) override;
        auto GetType() const -> const Interface::DynamicObjectType& override;

       public:
        void SetValueAsInt(
            const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type& value) override;
        void SetValueAsDouble(
            const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type& value) override;
        void SetValueAsString(
            const Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type& value) override;

       public:
        auto GetValueAsInt() const
            -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicObjectType<Interface::DynamicObjectType::String>::type& override;

        virtual void AssertTypeIs(const Interface::DynamicObjectType& type) const;
        virtual void AssertTypeIsNot(const Interface::DynamicObjectType& type) const;

       public:
        bool Equal(const IDynamicObject& element) override;
        bool NotEqual(const IDynamicObject& element) override;
        bool GreaterThan(const IDynamicObject& element) override;
        bool LessThan(const IDynamicObject& element) override;
        bool GreaterThanOrEqualTo(const IDynamicObject& element) override;
        bool LessThanOrEqualTo(const IDynamicObject& element) override;

       public:
        template <Interface::DynamicObjectType DynType>
        void SetValue(const typename Interface::GetDynamicObjectType<DynType>::type& value)
        {
            SetType(DynType);
            m_value = value;
        }
        template <Interface::DynamicObjectType DynType>
        auto GetValue() const -> typename Interface::GetDynamicObjectType<DynType>::type
        {
            return std::get<typename Interface::GetDynamicObjectType<DynType>::type>(m_value);
        }

       protected:
        Interface::DynamicObjectType m_type = Interface::DynamicObjectType::Unset;
        DynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
