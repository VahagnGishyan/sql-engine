
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT RowElement : public Interface::IRowElement
    {
       protected:
        using DynamicValue = Interface::DynamicValue;
        using IRowElement  = Interface::IRowElement;
        using URowElement  = Interface::URowElement;

       protected:
        RowElement(const unsigned int columnIndex, const DynamicValue& value);

       public:
        static auto Create(const unsigned int columnIndex,
                           const DynamicValue& value) -> Interface::URowElement;
        static auto Create(const IRowElement& element)
            -> Interface::URowElement;

       public:
        auto Copy() const -> URowElement override;

       public:
        auto GetColumnIndex() const -> const unsigned int override;
        void SetColumnIndex(const unsigned int) override;

       public:
        void SetValue(const DynamicValue& value) override;
        void SetValue(const IRowElement& element) override;
        auto GetValue() -> DynamicValue& override;
        auto GetValue() const -> const DynamicValue& override;

       public:
        bool Equal(const DynamicValue& value) const override;
        bool Equal(const IRowElement& element) const override;

        bool NotEqual(const DynamicValue& value) const override;
        bool NotEqual(const IRowElement& element) const override;

        bool GreaterThan(const DynamicValue& value) const override;
        bool GreaterThan(const IRowElement& element) const override;

        bool LessThan(const DynamicValue& value) const override;
        bool LessThan(const IRowElement& element) const override;

        bool GreaterThanOrEqualTo(const DynamicValue& value) const override;
        bool GreaterThanOrEqualTo(const IRowElement& element) const override;

        bool LessThanOrEqualTo(const DynamicValue& value) const override;
        bool LessThanOrEqualTo(const IRowElement& element) const override;

       protected:
        unsigned int m_columnIndex;
        DynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
