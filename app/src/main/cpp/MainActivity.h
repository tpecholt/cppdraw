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
    bool lightMode = true;
    /// @end interface

    void GoTo(int, int);

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
    void OnLightMode();

    bool setEditorFocus;
    TextEditor textEdit;
    TextEditor::Palette lightPalette;
    TextEditor::Palette darkPalette;
    TextEditor::Palette retroPalette;
    /// @end impl

    bool startProgram = false;

    void DoSaveFile(const std::string& fname);
};

extern MainActivity mainActivity;
