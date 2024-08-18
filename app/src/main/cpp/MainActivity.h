// Generated with ImRAD 0.8
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
    void NewFile(const std::string& fname);
    void SaveFile(const std::string& fname);

private:
    /// @begin impl
    void ResetLayout();
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
    void OnCopyAll();
    void OnIncreaseSize();
    void OnDecreaseSize();

    ImRad::HBox hb21;
    /// @end impl

    bool setEditorFocus;
    TextEditor textEdit;
    float teScrollY = 0;
    float teContentSizeY = 0;
    TextEditor::Palette lightPalette;
    TextEditor::Palette darkPalette;
    TextEditor::Palette retroPalette;
    bool startProgram = false;
};

extern MainActivity mainActivity;
