// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "InputQuery.h"
#include "MessageBox.h"

InputQuery inputQuery;


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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, 5*dp });
    ImGui::SetNextWindowPos(ioUserData->WorkRect().Min);  //Top
    ImGui::SetNextWindowSize({ ioUserData->WorkRect().GetWidth(), 0 }); //{ 640*dp, 480*dp }
    bool tmpOpen = true;
    if (ImGui::BeginPopupModal("title###InputQuery", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
    {
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
        if (ImGui::IsWindowAppearing())
            ImGui::SetKeyboardFocusHere();
        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##value", &value, ImGuiInputTextFlags_None);
        if (ImGui::IsItemActive())
            ioUserData->imeType = ImRad::ImeText;
        /// @end Input

        /// @begin Table
        ImRad::Spacing(2);
        if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_NoPadInnerX, { -1, 0 }))
        {
            ImGui::TableSetupColumn("left-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableSetupColumn("content", ImGuiTableColumnFlags_WidthFixed, 0*dp);
            ImGui::TableNextRow(0, 0);
            ImGui::TableSetColumnIndex(0);
            /// @separator

            /// @begin Button
            ImRad::TableNextColumn(1);
            if (ImGui::Button("OK", { 100*dp, 30*dp }))
            {
                ClosePopup(ImRad::Ok);
            }
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            if (ImGui::Button("Cancel", { 100*dp, 30*dp }) ||
                (!ImRad::IsItemDisabled() && ImGui::IsKeyPressed(ImGuiKey_Escape, false)))
            {
                ClosePopup(ImRad::Cancel);
            }
            /// @end Button


            /// @separator
            ImGui::EndTable();
        }
        /// @end Table

        /// @separator
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    /// @end TopWindow
}
