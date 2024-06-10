// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"
#include "ImGuiColorTextEdit/TextEditor.h"

class MainActivity
{
public:
    /// @begin interface
    void Open();

    void Draw();

    std::string fileName;
    bool darkMode = false;
    bool retroMode = false;
    bool vsMode = true;
    /// @end interface

private:
    /// @begin impl
    void Init();

    void OnEditor(const ImRad::CustomWidgetArgs& args);
    void OnButton();
    void OnButtonFocused();
    void OnRun();
    void OnFileNew();
    void OnFileOpen();
    void OnFileSaveAs();
    void OnFileDelete();
    void OnDarkMode();
    void OnRetroMode();
    void OnHelp();
    void OnVSMode();

    bool setFocus;
    TextEditor textEdit;
    /// @end impl

    void DoSaveFile(const std::string& fname);
};

extern MainActivity mainActivity;
