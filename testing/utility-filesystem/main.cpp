
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "testing/core/core.hpp"

#include "application-info/application.hpp"
#include "utility/filesystem.hpp"
#include "utility/core.hpp"

#include <iostream>
#include <gtest/gtest.h>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// TEST(UtilityFilesystem, Environment)
// {
// }

//////////////////////////////////////////////////////////////////////////

// TEST(UtilityFilesystem, Environment)
// {
// }

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

auto TestDirectoryPreparation() -> SQLEngine::Testing::Core::UDirectory
{
    using namespace SQLEngine::Testing::Core;

    auto &&info = SQLEngine::Application::GetInfo();
    const std::string path = info.GetDefaultAppData(false) + "/testing";
    SQLEngine::Utility::MakeDir(path);
    std::cout << "testing-path: " << path << std::endl;

    auto dir = Directory::CreateInstance("utility");
    dir->SetPath(path);

    {
        auto empty_dir = Directory::CreateInstance("empty-dir");
        dir->AddComponent(std::move(empty_dir));
    }

    {
        auto file = Directory::CreateInstance("1-file-dir");
        file->AddComponent(File::CreateInstance("file.txt"));
        dir->AddComponent(std::move(file));
    }

    auto AddFilesTo = [](Directory &dir, const int count)
    {
        for (int index = 0; index < count; ++index)
        {
            dir.AddComponent(File::CreateInstance("file-" + std::to_string(index) + ".txt"));
        }
    };

    auto AddEmptyDirsTo = [](Directory &dir, const int count)
    {
        for (int index = 0; index < count; ++index)
        {
            dir.AddComponent(Directory::CreateInstance("dir-" + std::to_string(index)));
        }
    };

    {
        auto ndir = Directory::CreateInstance("n-file-dir");
        AddFilesTo(*ndir, 10);
        dir->AddComponent(std::move(ndir));
    }

    {
        auto ndir = Directory::CreateInstance("n-dirs");
        AddEmptyDirsTo(*ndir, 10);
        dir->AddComponent(std::move(ndir));
    }

    {
        auto comp = Directory::CreateInstance("comp-dir");
        AddFilesTo(*comp, 10);
        AddEmptyDirsTo(*comp, 10);
        dir->AddComponent(std::move(comp));
    }

    return dir;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    auto &&dir = TestDirectoryPreparation();
    dir->Create();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
