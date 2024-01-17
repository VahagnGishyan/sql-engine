
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <map>
#include <stdexcept>

#include "i-dynamic-types.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Interface::GetDynamicTypeNameAsString(const DynamicType& type)
        -> const std::string&
    {
        static std::map<DynamicType, std::string> elements = {
            {DynamicType::Int,    "Unset" },
            {DynamicType::Int,    "Int"   },
            {DynamicType::Double, "Double"},
            {DynamicType::String, "String"},
        };
        static auto end = elements.end();

        auto pos = elements.find(type);
        Utility::Assert(
            pos != end,
            fmt::format(
                "GetDynamicTypeNameAsString, unknown DynamicType, id is [{}]",
                (int)type));
        return pos->second;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool Interface::IsDynamicValueType(const DynamicValue& value,
                                       const DynamicType& type)
    {
        switch (type)
        {
            case DynamicType::Int:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::Int>::type>(value);
                break;
            case DynamicType::Double:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::Double>::type>(value);
                break;
            case DynamicType::String:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::String>::type>(value);
                break;
            default:
                throw std::logic_error{"Unknown DynamicValue type"};
        }
    }

    void Interface::AssertDynamicValueTypeIs(const DynamicValue& value,
                                             const DynamicType& type)
    {
        Utility::Assert(IsDynamicValueType(value, type),
                        "Interface::AssertDynamicValueTypeIs()");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
