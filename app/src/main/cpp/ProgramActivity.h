// Generated with ImRAD 0.7
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
};

extern ProgramActivity programActivity;
