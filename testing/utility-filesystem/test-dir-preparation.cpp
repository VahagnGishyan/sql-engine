
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

namespace SQLEngine::Testing::Peparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using namespace SQLEngine::Testing::Core;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto TestDir::GetTestingWorkDir() -> const std::string
    {
        auto &&info = SQLEngine::Application::GetInfo();
        return info.GetDefaultAppData(false) + "/testing";
    }
    auto TestDir::GetTestingName() -> const std::string
    {
        return "utility-fs";
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class TestDirImpl : public TestDir
    {
    public:
        TestDirImpl() : m_dir{nullptr}
        {
            auto &&workdir = GetTestingWorkDir();
            auto &&name = GetTestingName();
            SQLEngine::Utility::MakeDir(workdir, Utility::Option::ExistOk{true});

            auto dir = Directory::CreateInstance(name);
            dir->SetPath(workdir);
            SQLEngine::Utility::AssertDirNotExists(dir->GetPath() + '/' + dir->GetName());

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
        auto GetFileNInfo() const -> const ShFileNInfo override
        {
            constexpr int count = 10;
            auto &&obj = std::make_shared<FileNInfo>();
            for (int index = 0; index < count; ++index)
            {
                obj->filenameList.push_back("file-" + std::to_string(index) + ".txt");
            }
            return obj;
        }
        auto GetDirNInfo() const -> const ShDirNInfo override
        {
            auto &&obj = std::make_shared<DirNInfo>();
            constexpr int count = 10;
            for (int index = 0; index < count; ++index)
            {
                obj->dirnameList.push_back("dir-" + std::to_string(index));
            }
            return obj;
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
                info->paelist.push_back(PathAndExtension{"file-txt-0.txt", "txt"});
                info->paelist.push_back(PathAndExtension{"file-txt-1.txt", "txt"});
                info->paelist.push_back(PathAndExtension{"file-txt-2.txt", "txt"});
                info->paelist.push_back(PathAndExtension{"file-txt-3.txt", "txt"});
                info->paelist.push_back(PathAndExtension{"file-json-0.json", ".json"});
                info->paelist.push_back(PathAndExtension{"file-json-1.json", ".json"});
                info->paelist.push_back(PathAndExtension{"file-json-2.json", ".json"});
                info->paelist.push_back(PathAndExtension{"file-json-3.json", ".json"});
                info->paelist.push_back(PathAndExtension{"file-py-0.py", ".py"});
                info->paelist.push_back(PathAndExtension{"file-py-1.py", ".py"});
                info->paelist.push_back(PathAndExtension{"file-py-2.py", ".py"});
                info->paelist.push_back(PathAndExtension{"file-py-3.py", ".py"});
                info->paelist.push_back(PathAndExtension{"file-cpp-0.cpp", ".cpp"});
                info->paelist.push_back(PathAndExtension{"file-cpp-1.cpp", ".cpp"});
                info->paelist.push_back(PathAndExtension{"file-cpp-2.cpp", ".cpp"});
                info->paelist.push_back(PathAndExtension{"file-cpp-3.cpp", ".cpp"});
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
                info->paelist.push_back(PathAndExtension{"file", ".py"});
                return info;
            }();
            return info;
        }

    protected:
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
        void AddFilesTo(Directory &dir, const FileNInfo &files) const
        {
            for (auto &&file : files.filenameList)
            {
                dir.AddComponent(File::CreateInstance(file));
            }
        }
        void AddEmptyDirsTo(Directory &dir, const DirNInfo &dirs) const
        {
            for (auto &&dirinfo : dirs.dirnameList)
            {
                dir.AddComponent(Directory::CreateInstance(dirinfo));
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
            auto &&filelist = GetFileNInfo();
            AddFilesTo(*ndir, *filelist);
            dir.AddComponent(std::move(ndir));
        }
        void CreateDirNDir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&dirname = GetDirNName();
            auto ndir = Directory::CreateInstance(dirname);
            ndir->SetPath(workdir);
            auto &&dirlist = GetDirNInfo();
            AddEmptyDirsTo(*ndir, *dirlist);
            dir.AddComponent(std::move(ndir));
        }
        void CreateCompDir(Directory &dir) const
        {
            auto &&workdir = GetWorkDir();
            auto &&compdirname = GetCompDirName();
            auto comp = Directory::CreateInstance(compdirname);
            comp->SetPath(workdir);
            auto &&filelist = GetFileNInfo();
            AddFilesTo(*comp, *filelist);
            auto &&dirlist = GetDirNInfo();
            AddEmptyDirsTo(*comp, *dirlist);
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
