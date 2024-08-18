// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class ProgramActivity
{
public:
    /// @begin interface
    void Open();
    void Draw();

    /// @end interface

private:
    /// @begin impl
    void Init();

    void OnQuit();
    void OnDraw(const ImRad::CustomWidgetArgs& args);

    /// @end impl

    void Connect();
    int sockfd = 0;
    std::string error;
    float timeStart;
    float lastTime;
    ImVec2 lastMousePos;
    std::vector<char> strBuf, buf;
};

extern ProgramActivity programActivity;
