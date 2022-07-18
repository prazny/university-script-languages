#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio>
#include <ctime>
#include <cstring>

using namespace std;
namespace fs = std::filesystem;

template <typename TP>
std::time_t to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

struct File {
    string fileName;
    unsigned long long fileSize{};
    time_t fileModDate{};

    File makeFile(const fs::directory_entry& entry) {
        fileName = entry.path().u8string();
        fileModDate = to_time_t(entry.last_write_time());
        if(!entry.is_directory())
            fileSize = entry.file_size();
        else fileSize = 0;
        return *this;
    }
};

struct alphaPathComparator
{
    inline bool operator() (const File& file1, const File& file2)
    {
        return (file1.fileName < file2.fileName);
    }
};
struct datePathComparator
{
    inline bool operator() (const File& file1, const File& file2)
    {
        return (file1.fileModDate > file2.fileModDate);
    }
};

bool isStringEquals(const char *string1, const char *string2) {
    if(strlen(string1) != strlen(string2)) return false;

    for (int i = 0; i < strlen(string1); i++)
        if(string1[i] != string2[i]) return false;

    return true;
}


void getPaths(const fs::path& currentPath, vector<File> *pathList, bool isOnlyDirectories, bool isRecursive) {
    for (auto &file: filesystem::directory_iterator(currentPath)) {
        if(isOnlyDirectories) {
            if(file.is_directory())
                pathList->push_back((new File)->makeFile(file));
        } else
            pathList->push_back((new File)->makeFile(file));

        if(isRecursive && file.is_directory())
            getPaths(file, pathList, isOnlyDirectories, isRecursive);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    vector<File> *paths;
    paths = new vector<File>();

    bool isOnlyDirectories=false, isRecursive=false, isShowSize=false;
    enum Sort {none, date, alpha};
    Sort sortBy = none;
    string sort;

    for (int i = 0; i < argc; i++) {
        if (isStringEquals(argv[i], "-R"))
            isRecursive = true;
        else if (isStringEquals(argv[i], "-d"))
            isOnlyDirectories = true;
        else if (isStringEquals(argv[i], "-s"))
            isShowSize = true;
        else if (isStringEquals(argv[i], "--sort=alpha"))
            sortBy = alpha;
        else if (isStringEquals(argv[i], "--sort=date"))
            sortBy = date;
    }
    getPaths(filesystem::current_path(), paths, isOnlyDirectories, isRecursive);
    if(sortBy == alpha)
        std::sort(paths->begin(), paths->end(), alphaPathComparator());
    else if(sortBy == date)
        std::sort(paths->begin(), paths->end(), datePathComparator());



    for(auto & file : *paths) {
        cout <<file.fileName;
        if(isShowSize) cout <<" -> "<<file.fileSize;
        cout<<endl;
    }

    paths->clear();
    delete paths;

    return 0;
}