// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class MessageBox
{
public:
    /// @begin interface
    void OpenPopup(std::function<void(ImRad::ModalResult)> clb = [](ImRad::ModalResult){});
    void ClosePopup(ImRad::ModalResult mr = ImRad::Cancel);
    void Draw();

    std::string message;
    int buttons = ImRad::Ok;
    int kok = 0;
    /// @end interface

private:
    /// @begin impl
    void ResetLayout();
    void Init();

    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    std::function<void(ImRad::ModalResult)> callback;
    ImRad::HBox hb1;
    ImRad::HBox hb2;
    /// @end impl
};

extern MessageBox messageBox;
