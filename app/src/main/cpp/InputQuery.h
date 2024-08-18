// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#pragma once
#include "imrad.h"

class InputQuery
{
public:
    /// @begin interface
    void OpenPopup(std::function<void(ImRad::ModalResult)> clb = [](ImRad::ModalResult){});
    void ClosePopup(ImRad::ModalResult mr = ImRad::Cancel);
    void Draw();

    std::string label;
    std::string value;
    /// @end interface

    void EnterFileName(const std::string& label, std::function<void(const std::string&)> clb);

private:
    /// @begin impl
    void ResetLayout();
    void Init();

    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    std::function<void(ImRad::ModalResult)> callback;
    ImRad::HBox hb3;
    /// @end impl
};

extern InputQuery inputQuery;
