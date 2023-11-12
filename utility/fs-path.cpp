

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

#include "filesystem.hpp"
#include "core.hpp"

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

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
