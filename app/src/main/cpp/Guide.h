// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class Guide
{
public:
    /// @begin interface
    void OpenPopup(std::function<void(ImRad::ModalResult)> clb = [](ImRad::ModalResult){});
    void ClosePopup(ImRad::ModalResult mr = ImRad::Cancel);
    void Draw();

    /// @end interface

private:
    /// @begin impl
    void Init();

    void OnGuide(const ImRad::CustomWidgetArgs& args);

    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    ImRad::Animator animator;
    ImVec2 animPos;
    std::function<void(ImRad::ModalResult)> callback;
    std::string content;
    /// @end impl
};

extern Guide guide;
