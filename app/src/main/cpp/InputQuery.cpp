// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#include "InputQuery.h"
#include "MessageBox.h"

InputQuery inputQuery;

namespace fs = std::filesystem;

void InputQuery::OpenPopup(std::function<void(ImRad::ModalResult)> clb)
{
    callback = clb;
    modalResult = ImRad::None;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    ioUserData->dimBgRatio = 1.f;
    ImGui::OpenPopup(ID);
    Init();
}

void InputQuery::ClosePopup(ImRad::ModalResult mr)
{
    modalResult = mr;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    ioUserData->dimBgRatio = 0.f;
}

void InputQuery::Init()
{
    // TODO: Add your code here
}

void InputQuery::Draw()
{
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    ID = ImGui::GetID("###InputQuery");
    ImGui::PushStyleColor(ImGuiCol_PopupBg, 0xff323432);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, 5*dp });
    ImGui::SetNextWindowPos(ioUserData->WorkRect().Min);  //Top
    ImGui::SetNextWindowSize({ ioUserData->WorkRect().GetWidth(), 0 }); //{ 640*dp, 480*dp }
    bool tmpOpen = true;
    if (ImGui::BeginPopupModal("title###InputQuery", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ioUserData->activeActivity != "")
            ImRad::RenderDimmedBackground(ioUserData->WorkRect(), ioUserData->dimBgRatio);
        ImRad::RenderFilledWindowCorners(ImDrawFlags_RoundCornersTop);
        if (modalResult != ImRad::None)
        {
            ImGui::CloseCurrentPopup();
            if (modalResult != ImRad::Cancel)
                callback(modalResult);
        }
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here
        messageBox.Draw();

        /// @begin Text
        ImGui::TextUnformatted(ImRad::Format("{}", label).c_str());
        /// @end Text

        /// @begin Input
        ImRad::Spacing(1);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, 0x00ffffff);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1*dp);
        if (ImGui::IsWindowAppearing())
            ImGui::SetKeyboardFocusHere();
        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##value", &value, ImGuiInputTextFlags_None);
        if (ImGui::IsItemActive())
            ioUserData->imeType = ImRad::ImeText;
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        /// @end Input

        /// @begin Spacer
        ImRad::Spacing(2);
        hb3.BeginLayout();
        ImRad::Dummy({ hb3.GetSize(), 0 });
        hb3.AddSize(0, ImRad::HBox::Stretch);
        /// @end Spacer

        /// @begin Button
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::BeginDisabled(value.empty());
        ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1*dp);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10*dp);
        if (ImGui::Button("OK", { 80*dp, 30*dp }))
        {
            ClosePopup(ImRad::Ok);
        }
        hb3.AddSize(1, 80*dp);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::EndDisabled();
        /// @end Button

        /// @begin Button
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1*dp);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10*dp);
        if (ImGui::Button("Cancel", { 80*dp, 30*dp }) ||
            ImGui::Shortcut(ImGuiKey_Escape))
        {
            ClosePopup(ImRad::Cancel);
        }
        hb3.AddSize(1, 80*dp);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        /// @end Button

        /// @separator
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    /// @end TopWindow
}

void InputQuery::EnterFileName(const std::string& l, std::function<void(const std::string&)> clb)
{
    label = l;
    value = "";
    OpenPopup([this,clb](ImRad::ModalResult) {
        std::string fn = value;
        if (fn.find(".") == std::string::npos)
            fn += ".cpp";
        if (fs::exists(/*homeDir + "/" +*/ fn)) {
            messageBox.buttons = ImRad::Yes | ImRad::No;
            messageBox.message = "'" + fn + "' already exists. Overwrite?";
            messageBox.OpenPopup([fn,clb](ImRad::ModalResult mr) {
                if (mr == ImRad::Yes)
                    clb(fn);
            });
        }
        else {
            clb(fn);
        }
    });
}

void InputQuery::ResetLayout()
{
    // ImGui::GetCurrentWindow()->HiddenFramesCannotSkipItems = 2;
    hb3.Reset();
}
