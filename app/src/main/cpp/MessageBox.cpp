// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#include "MessageBox.h"

MessageBox messageBox;


void MessageBox::OpenPopup(std::function<void(ImRad::ModalResult)> clb)
{
    callback = clb;
    modalResult = ImRad::None;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    ioUserData->dimBgRatio = 1.f;
    ImGui::OpenPopup(ID);
    Init();
}

void MessageBox::ClosePopup(ImRad::ModalResult mr)
{
    modalResult = mr;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    ioUserData->dimBgRatio = 0.f;
}

void MessageBox::Init()
{
    // TODO: Add your code here
    ResetLayout();
}

void MessageBox::Draw()
{
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    ID = ImGui::GetID("###MessageBox");
    ImGui::PushStyleColor(ImGuiCol_PopupBg, 0xff323432);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, 5*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5*dp);
    ImGui::SetNextWindowPos(ioUserData->WorkRect().GetCenter(), 0, { 0.5f, 0.5f }); //Center
    ImGui::SetNextWindowSize({ 0, 0 }); //{ 640*dp, 480*dp }
    bool tmpOpen = true;
    if (ImGui::BeginPopupModal("title###MessageBox", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ioUserData->activeActivity != "")
            ImRad::RenderDimmedBackground(ioUserData->WorkRect(), ioUserData->dimBgRatio);
        if (modalResult != ImRad::None)
        {
            ImGui::CloseCurrentPopup();
            if (modalResult != ImRad::Cancel)
                callback(modalResult);
        }
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin Spacer
        hb1.BeginLayout();
        ImRad::Dummy({ hb1.GetSize(), 0 });
        hb1.AddSize(0, ImRad::HBox::Stretch(1));
        /// @end Spacer

        /// @begin Text
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::TextUnformatted(ImRad::Format("{}", message).c_str());
        hb1.AddSize(1, ImRad::HBox::ItemSize);
        /// @end Text

        /// @begin Spacer
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImRad::Dummy({ hb1.GetSize(), 0 });
        hb1.AddSize(1, ImRad::HBox::Stretch(1));
        /// @end Spacer

        /// @begin Spacer
        hb2.BeginLayout();
        ImRad::Spacing(4);
        ImRad::Dummy({ hb2.GetSize(), 0 });
        hb2.AddSize(0, ImRad::HBox::Stretch(1));
        /// @end Spacer

        /// @begin Button
        if (buttons&ImRad::Ok)
        {
            //visible
            ImGui::SameLine(0, 0 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Text, 0xff000000);
            ImGui::PushStyleColor(ImGuiCol_Button, 0xffd2d2d2);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0*dp);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15*dp);
            if (ImGui::Button("OK", { 80*dp, 30*dp }))
            {
                ClosePopup(ImRad::Ok);
            }
            hb2.AddSize(0, 80*dp);
            ImGui::PopStyleVar();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }
        /// @end Button

        /// @begin Button
        if (buttons&ImRad::Yes)
        {
            //visible
            ImGui::SameLine(0, 0 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Text, 0xff000000);
            ImGui::PushStyleColor(ImGuiCol_Button, 0xffd2d2d2);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0*dp);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15*dp);
            if (ImGui::Button("Yes", { 80*dp, 30*dp }))
            {
                ClosePopup(ImRad::Yes);
            }
            hb2.AddSize(0, 80*dp);
            ImGui::PopStyleVar();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }
        /// @end Button

        /// @begin Button
        if (buttons&ImRad::No)
        {
            //visible
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1*dp);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15*dp);
            if (ImGui::Button("No", { 80*dp, 30*dp }))
            {
                ClosePopup(ImRad::No);
            }
            hb2.AddSize(1, 80*dp);
            ImGui::PopStyleVar();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
        }
        /// @end Button

        /// @begin Button
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1*dp);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15*dp);
        if (ImGui::Button("Cancel", { 80*dp, 30*dp }) ||
            ImGui::Shortcut(ImGuiKey_Escape))
        {
            ClosePopup(ImRad::Cancel);
        }
        hb2.AddSize(1, 80*dp);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        /// @end Button

        /// @separator
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    /// @end TopWindow
}

void MessageBox::ResetLayout()
{
    // ImGui::GetCurrentWindow()->HiddenFramesCannotSkipItems = 2;
    hb1.Reset();
    hb2.Reset();
}
