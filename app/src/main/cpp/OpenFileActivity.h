// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class OpenFileActivity
{
public:
    /// @begin interface
    void Open();

    void Draw();

    struct FileInfo {
        time_t time;
        std::string name;
        std::string size;
        std::string modified;
    };
    std::vector<FileInfo> files;
    int r = 0;
    /// @end interface

private:
    /// @begin impl
    void Init();

    void OnClose();
    void OnSelect();

    /// @end impl
};

extern OpenFileActivity openFileActivity;
