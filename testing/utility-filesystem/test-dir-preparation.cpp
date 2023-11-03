
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "test-dir-preparation.hpp"
#include "testing/core/core.hpp"
#include "application-info/application.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

#include <iostream>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::DirPeparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using namespace SQLEngine::Testing::Core;

    class TestDirImpl : public TestDir
    {
    public:
        TestDirImpl() : m_dir{nullptr}
        {
            auto &&workdir = GetTestingWorkDir();
            auto &&name = GetTestingName();
            SQLEngine::Utility::MakeDir(workdir);

            auto dir = Directory::CreateInstance(name);
            dir->SetPath(workdir);

            CreateEmptyDir(*dir);
            CreateFile1Dir(*dir);
            CreateFileNDir(*dir);
            CreateDirNDir(*dir);
            CreateCompDir(*dir);

            dir->Create();

            m_dir = std::move(dir);
        }

    public:
        auto GetWorkDir() const -> const std::string override
        {
            const std::string path = GetTestingWorkDir() + '/' + GetTestingName();
            std::cout << "testing-path: " << path << std::endl;
            return path;
        }
        auto GetEmptyDirPath() const -> const std::string override
        {
            return GetWorkDir() + "/empty-dir";
        }
        auto GetFile1Path() const -> const std::string override
        {
            return GetWorkDir() + "/file-1-dir";
        }
        auto GetFileNPath() const -> const std::string override
        {
            return GetWorkDir() + "/file-n-dir";
        }
        auto GetDirNPath() const -> const std::string override
        {
            return GetWorkDir() + "/dir-n-dir";
        }
        auto GetFileNDirNPath() const -> const std::string override
        {
            return GetWorkDir() + "/comp-dir";
        }

    protected:
        auto GetTestingWorkDir() const -> const std::string
        {
            auto &&info = SQLEngine::Application::GetInfo();
            return info.GetDefaultAppData(false) + "/testing";
        }
        auto GetTestingName() const -> const std::string
        {
            return "utility-fs";
        }

    protected:
        void AddFilesTo(Directory &dir, const int count) const
        {
            for (int index = 0; index < count; ++index)
            {
                dir.AddComponent(File::CreateInstance("file-" + std::to_string(index) + ".txt"));
            }
        }
        void AddEmptyDirsTo(Directory &dir, const int count) const
        {
            for (int index = 0; index < count; ++index)
            {
                dir.AddComponent(Directory::CreateInstance("dir-" + std::to_string(index)));
            }
        }

    protected:
        void CreateEmptyDir(Directory &dir) const
        {
            auto &&emptyDirPath = GetEmptyDirPath();
            auto empty_dir = Directory::CreateInstance(emptyDirPath);
            dir.AddComponent(std::move(empty_dir));
        }
        void CreateFile1Dir(Directory &dir) const
        {
            auto &&file1dir = GetFile1Path();
            auto file = Directory::CreateInstance(file1dir);

            file->AddComponent(File::CreateInstance("file.txt"));
            dir.AddComponent(std::move(file));
        }
        void CreateFileNDir(Directory &dir) const
        {
            auto &&fileNdir = GetFileNPath();
            auto ndir = Directory::CreateInstance(fileNdir);
            AddFilesTo(*ndir, 10);
            dir.AddComponent(std::move(ndir));
        }
        void CreateDirNDir(Directory &dir) const
        {
            auto &&dirNdir = GetDirNPath();
            auto ndir = Directory::CreateInstance(dirNdir);
            AddEmptyDirsTo(*ndir, 10);
            dir.AddComponent(std::move(ndir));
        }
        void CreateCompDir(Directory &dir) const
        {
            auto &&compdir = GetFileNDirNPath();
            auto comp = Directory::CreateInstance(compdir);
            AddFilesTo(*comp, 10);
            AddEmptyDirsTo(*comp, 10);
            dir.AddComponent(std::move(comp));
        }

    protected:
        UDirectory m_dir;
    };

    //////////////////////////////////////////////////////////////////////

    auto GetTestDir() -> const TestDir &
    {
        static TestDirImpl obj{};
        return obj;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
