
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <map>
#include <stdexcept>

#include "i-element.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto GetElementTypeNameAsString(const ElementType& type) -> const std::string&
    {
        static std::map<ElementType, std::string> elements = {
            {ElementType::Int,    "Unset" },
            {ElementType::Int,    "Int"   },
            {ElementType::Double, "Double"},
            {ElementType::String, "String"},
        };
        static auto end = elements.end();

        auto pos = elements.find(type);
        Utility::Assert(pos != end,
                        fmt::format("GetElementTypeNameAsString, unknown ElementType, id is [{}]", (int)type));
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
