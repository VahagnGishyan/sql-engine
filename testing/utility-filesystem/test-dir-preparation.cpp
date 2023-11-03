
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
            CreateFilesValidPAE(*dir);

            dir->Create();

            m_dir = std::move(dir);
        }

    public:
        auto GetWorkDir() const -> const std::string override
        {
            const std::string path = GetTestingWorkDir() + '/' + GetTestingName();
            return path;
        }
        auto GetEmptyDirPath() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetEmptyDirName();
        }
        auto GetFile1Path() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetFile1Name();
        }
        auto GetEmptyFilePath() const -> const std::string override
        {
            return GetFile1Path() + "/" + GetEmptyFileName();
        }
        auto GetFileNPath() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetFileNName();
        }
        auto GetDirNPath() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetDirNName();
        }
        auto GetCompDirPath() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetCompDirName();
        }
        auto GetNonExistingPath() const -> const std::string override
        {
            return GetWorkDir() + "/" + GetNonExistingName();
        }
        auto GetValidFilePAEList() const -> const ShDirOfPAE override
        {
            static auto &&info = [this]()
            {
                auto &&info = std::make_shared<DirOfPAE>();
                info->dirpath = GetWorkDir() + "/" + GetValidFilePAEListDirName();
                info->paelist.push_back(PathAndExtension{"file-txt-low.txt", "txt"});
                info->paelist.push_back(PathAndExtension{"file-txt-up.TXT", ".txt"});
                info->paelist.push_back(PathAndExtension{"file.json", ".json"});
                info->paelist.push_back(PathAndExtension{"file.png", ".png"});
                info->paelist.push_back(PathAndExtension{"file.jpg", ".jpg"});
                return info;
            }();
            return info;
        }
        auto GetInvalidFilePAEList() const -> const ShDirOfPAE override
        {
            static auto &&info = [this]()
            {
                auto &&info = std::make_shared<DirOfPAE>();
                info->dirpath = GetWorkDir() + "/" + GetInvalidFilePAEListDirName();
                info->paelist.push_back(PathAndExtension{"file-txt.txt", "aaa"});
                info->paelist.push_back(PathAndExtension{"file-txt.TXT", ".json"});
                info->paelist.push_back(PathAndExtension{"file.json", "txt"});
                info->paelist.push_back(PathAndExtension{"file", ".png"});
                return info;
            }();
            return info;
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
        auto GetEmptyDirName() const -> const std::string
        {
            return "empty-dir";
        }
        auto GetFile1Name() const -> const std::string
        {
            return "file-1-dir";
        }
        auto GetEmptyFileName() const -> const std::string
        {
            return "file.txt";
        }
        auto GetFileNName() const -> const std::string
        {
            return "file-n-dir";
        }
        auto GetDirNName() const -> const std::string
        {
            return "dir-n-dir";
        }
        auto GetCompDirName() const -> const std::string
        {
            return "comp-dir";
        }
        auto GetNonExistingName() const -> const std::string
        {
            return "nonexisting__";
        }
        auto GetValidFilePAEListDirName() const -> const std::string
        {
            return "path-and-extension-valid";
        }
        auto GetInvalidFilePAEListDirName() const -> const std::string
        {
            return "path-and-extension-invalid";
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
            auto &&workdir = GetWorkDir();
            auto &&dirname = GetEmptyDirName();
            auto empty_dir = Directory::CreateInstance(dirname);
            empty_dir->SetPath(workdir);
            dir.AddComponent(std::move(empty_dir));
        }
        void CreateFile1Dir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&dirname = GetFile1Name();
            auto file = Directory::CreateInstance(dirname);
            file->SetPath(workdir);

            const std::string filename = GetEmptyFileName();
            file->AddComponent(File::CreateInstance(filename));
            dir.AddComponent(std::move(file));
        }
        void CreateFileNDir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&fileNdir = GetFileNName();
            auto ndir = Directory::CreateInstance(fileNdir);
            ndir->SetPath(workdir);
            AddFilesTo(*ndir, 10);
            dir.AddComponent(std::move(ndir));
        }
        void CreateDirNDir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&dirname = GetDirNName();
            auto ndir = Directory::CreateInstance(dirname);
            ndir->SetPath(workdir);
            AddEmptyDirsTo(*ndir, 10);
            dir.AddComponent(std::move(ndir));
        }
        void CreateCompDir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&compdirname = GetCompDirName();
            auto comp = Directory::CreateInstance(compdirname);
            comp->SetPath(workdir);
            AddFilesTo(*comp, 10);
            AddEmptyDirsTo(*comp, 10);
            dir.AddComponent(std::move(comp));
        }
        void CreateFilesValidPAE(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&pae = GetValidFilePAEList();
            auto &&paedirName = GetValidFilePAEListDirName();
            auto comp = Directory::CreateInstance(paedirName);
            comp->SetPath(workdir);
            for (auto &&item : pae->paelist)
            {
                comp->AddComponent(File::CreateInstance(item.filename));
            }
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
