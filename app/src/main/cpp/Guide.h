// Generated with ImRAD 0.7
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
    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    ImRad::Animator animator;
    ImVec2 animPos;
    std::function<void(ImRad::ModalResult)> callback;

    void OnGuide(const ImRad::CustomWidgetArgs& args);

    std::string content;
    /// @end impl
};

extern Guide guide;
