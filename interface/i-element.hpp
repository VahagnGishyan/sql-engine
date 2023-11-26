
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    enum class ElementType
    {
        Unset,
        Int,
        Double,
        String
    };

    auto GetElementTypeNameAsString(const ElementType& type) -> const std::string&;

    //////////////////////////////////////////////////////////////////////

    template <ElementType DynType>
    class GetElementType;

    template <>
    class GetElementType<ElementType::Int>
    {
       public:
        using type = int;
    };

    template <>
    class GetElementType<ElementType::Double>
    {
       public:
        using type = double;
    };

    template <>
    class GetElementType<ElementType::String>
    {
       public:
        using type = std::string;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDynamicValue
    {
       public:
        virtual ~IDynamicValue() = default;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IElement
    {
       public:
        virtual ~IElement() = default;

       public:
        virtual auto GetType() const -> const ElementType&    = 0;
        virtual auto GetValue() const -> const IDynamicValue& = 0;

        virtual void SetType(const ElementType& type)                                                   = 0;
        virtual void SetValue(const IDynamicValue& value, const ElementType& type = ElementType::Unset) = 0;

       public:
        virtual bool Equal(const IElement& element)                = 0;
        virtual bool NotEqual(const IElement& element)             = 0;
        virtual bool GreaterThan(const IElement& element)          = 0;
        virtual bool LessThan(const IElement& element)             = 0;
        virtual bool GreaterThanOrEqualTo(const IElement& element) = 0;
        virtual bool LessThanOrEqualTo(const IElement& element)    = 0;
    };

    using UElement  = std::unique_ptr<IElement>;
    using ShElement = std::shared_ptr<IElement>;
    using WElement  = std::weak_ptr<IElement>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
