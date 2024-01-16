
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

    class IColumnElement;

    using UColumnElement     = std::unique_ptr<IColumnElement>;
    using WColumnElement     = std::weak_ptr<IColumnElement>;
    using ShColumnElement    = std::shared_ptr<IColumnElement>;
    using ColumnElementList  = std::vector<UColumnElement>;
    using UColumnElementList = std::unique_ptr<ColumnElementList>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IColumnElement : public IColumnComponent
    {
       public:
        virtual auto Copy() const -> UColumnElement = 0;

       public:
        virtual void SetValue(const DynamicValue& value)     = 0;
        virtual void SetValue(const IColumnElement& element) = 0;
        virtual auto GetValue() -> DynamicValue&             = 0;
        virtual auto GetValue() const -> const DynamicValue& = 0;

       public:
        virtual bool Equal(const DynamicValue& value) const   = 0;
        virtual bool Equal(const IColumnElement& value) const = 0;

        virtual bool NotEqual(const DynamicValue& value) const   = 0;
        virtual bool NotEqual(const IColumnElement& value) const = 0;

        virtual bool GreaterThan(const DynamicValue& value) const   = 0;
        virtual bool GreaterThan(const IColumnElement& value) const = 0;

        virtual bool LessThan(const DynamicValue& value) const   = 0;
        virtual bool LessThan(const IColumnElement& value) const = 0;

        virtual bool GreaterThanOrEqualTo(const DynamicValue& value) const = 0;
        virtual bool GreaterThanOrEqualTo(
            const IColumnElement& value) const = 0;

        virtual bool LessThanOrEqualTo(const DynamicValue& value) const   = 0;
        virtual bool LessThanOrEqualTo(const IColumnElement& value) const = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
