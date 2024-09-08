// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class BuildOutput
{
public:
    struct OutputRow {
        enum Kind { note, warning, error };
        Kind kind = note;
        int line = 0, column = 0;
        std::string text;
    };

    /// @begin interface
    void OpenPopup();
    void ClosePopup();
    void Draw();

    std::vector<OutputRow> output;
    int sel = -1;
    float height = 0;
    /// @end interface

    int ParseOutput(std::string_view output, std::string_view fname);

private:
    /// @begin impl
    void Init();

    void OnBeginRow();
    void OnItemHovered();

    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    ImRad::Animator animator;
    ImVec2 animPos;
    int newSel;
    /// @end impl
};

extern BuildOutput buildOutput;
