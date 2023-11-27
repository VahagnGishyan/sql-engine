
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <map>
#include <stdexcept>

#include "i-dyn-object.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto GetDynamicTypeNameAsString(const DynamicType& type) -> const std::string&
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
            fmt::format("GetDynamicTypeNameAsString, unknown DynamicType, id is [{}]", (int)type));
        return pos->second;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
