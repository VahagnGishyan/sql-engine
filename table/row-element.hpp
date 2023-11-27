
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "dyn-object.hpp"
#include "interface/i-row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT RowElement : public Interface::IRowElement
    {
       public:
        auto Copy() const -> Interface::UDynamicObject override;

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

        virtual void AssertTypeIs(const Interface::DynamicType& type) const;
        virtual void AssertTypeIsNot(const Interface::DynamicType& type) const;

       public:
        bool Equal(const IDynamicObject& element) override;
        bool NotEqual(const IDynamicObject& element) override;
        bool GreaterThan(const IDynamicObject& element) override;
        bool LessThan(const IDynamicObject& element) override;
        bool GreaterThanOrEqualTo(const IDynamicObject& element) override;
        bool LessThanOrEqualTo(const IDynamicObject& element) override;

       protected:
        DynamicObject m_dynobj;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
