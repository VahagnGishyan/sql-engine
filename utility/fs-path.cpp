

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

#include "core.hpp"
#include "filesystem.hpp"

// #include <iostream>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace fs = std::filesystem;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Utility::IsPathExists(const std::string &path) -> bool
    {
        fs::path filePath(path);
        return fs::exists(filePath);
    }

    void Utility::AssertPathExists(const std::string &path)
    {
        Assert(IsPathExists(path), fmt::format("{} does not exist.", path));
    }

    /**
     * temp
     * absolute function are not tested
     */

    auto Utility::IsPathAbsolute(const std::string &path) -> bool
    {
        fs::path filePath(path);
        return filePath.is_absolute();
    }

    void Utility::AssertPathAbsolute(const std::string &path)
    {
        Assert(IsPathAbsolute(path), fmt::format("{} is not absolute.", path));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
