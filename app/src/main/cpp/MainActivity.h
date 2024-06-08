// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"
#include "TextEditor.h"

class MainActivity
{
public:
    /// @begin interface
    void Open();

    void Draw();

    std::string homeDir;
    std::string fileName;
    bool darkMode = true;
    bool retroMode = false;
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

    bool setFocus;
    TextEditor textEdit;
    /// @end impl

    void SaveFile(const std::string& fname);
};

extern MainActivity mainActivity;
