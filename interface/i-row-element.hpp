
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "i-db-object.hpp"
#include "i-dynamic-types.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IRowElement;

    using URowElement     = std::unique_ptr<IRowElement>;
    using WRowElement     = std::weak_ptr<IRowElement>;
    using ShRowElement    = std::shared_ptr<IRowElement>;
    using RowElementList  = std::vector<URowElement>;
    using URowElementList = std::unique_ptr<RowElementList>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IRowElement : public IRowComponent
    {
       public:
        virtual auto Copy() const -> URowElement = 0;

       public:
        virtual auto GetRowIndex() const -> const unsigned int = 0;
        virtual void SetRowIndex(const unsigned int)           = 0;

       public:
        virtual void SetValue(const DynamicValue& value)     = 0;
        virtual void SetValue(const IRowElement& element)    = 0;
        virtual auto GetValue() -> DynamicValue&             = 0;
        virtual auto GetValue() const -> const DynamicValue& = 0;

       public:
        virtual bool Equal(const DynamicValue& value) const = 0;
        virtual bool Equal(const IRowElement& value) const  = 0;

        virtual bool NotEqual(const DynamicValue& value) const = 0;
        virtual bool NotEqual(const IRowElement& value) const  = 0;

        virtual bool GreaterThan(const DynamicValue& value) const = 0;
        virtual bool GreaterThan(const IRowElement& value) const  = 0;

        virtual bool LessThan(const DynamicValue& value) const = 0;
        virtual bool LessThan(const IRowElement& value) const  = 0;

        virtual bool GreaterThanOrEqualTo(const DynamicValue& value) const = 0;
        virtual bool GreaterThanOrEqualTo(const IRowElement& value) const  = 0;

        virtual bool LessThanOrEqualTo(const DynamicValue& value) const = 0;
        virtual bool LessThanOrEqualTo(const IRowElement& value) const  = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
