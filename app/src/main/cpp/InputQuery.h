// Generated with ImRAD 0.7
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

private:
    /// @begin impl
    void Init();
    ImGuiID ID = 0;
    ImRad::ModalResult modalResult;
    std::function<void(ImRad::ModalResult)> callback;


    /// @end impl
};

extern InputQuery inputQuery;
