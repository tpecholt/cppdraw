// Generated with ImRAD 0.7
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
}

void MessageBox::Draw()
{
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    ID = ImGui::GetID("###MessageBox");
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, 5*dp });
    ImGui::SetNextWindowSize({ 0, 0 }); //{ 640*dp, 480*dp }
    bool tmpOpen = true;
    if (ImGui::BeginPopupModal("title###MessageBox", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (modalResult != ImRad::None)
        {
            ImGui::CloseCurrentPopup();
            if (modalResult != ImRad::Cancel)
                callback(modalResult);
        }
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin Table
        if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_NoPadInnerX, { -1, 0 }))
        {
            ImGui::TableSetupColumn("left-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableSetupColumn("content", ImGuiTableColumnFlags_WidthFixed, 0*dp);
            ImGui::TableSetupColumn("right-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableNextRow(0, 0);
            ImGui::TableSetColumnIndex(0);
            /// @separator

//TODO: Add Draw calls of dependent popup windows here
            /// @begin Text
            ImRad::TableNextColumn(1);
            ImGui::TextUnformatted(ImRad::Format("{}", message).c_str());
            /// @end Text


            /// @separator
            ImGui::EndTable();
        }
        /// @end Table

        /// @begin Table
        ImRad::Spacing(2);
        if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_NoPadInnerX, { -1, 0 }))
        {
            ImGui::TableSetupColumn("left-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableSetupColumn("content", ImGuiTableColumnFlags_WidthFixed, 0*dp);
            ImGui::TableSetupColumn("right-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableNextRow(0, 0);
            ImGui::TableSetColumnIndex(0);
            /// @separator

            /// @begin Button
            ImRad::TableNextColumn(1);
            if (buttons&ImRad::Ok)
            {
                //visible
                if (ImGui::Button("OK", { 100*dp, 30*dp }))
                {
                    ClosePopup(ImRad::Ok);
                }
            }
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            if (buttons&ImRad::Cancel)
            {
                //visible
                if (ImGui::Button("Cancel", { 100*dp, 30*dp }) ||
                    (!ImRad::IsItemDisabled() && ImGui::IsKeyPressed(ImGuiKey_Escape, false)))
                {
                    ClosePopup(ImRad::Cancel);
                }
            }
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            if (buttons&ImRad::Yes)
            {
                //visible
                if (ImGui::Button("Yes", { 100*dp, 30*dp }))
                {
                    ClosePopup(ImRad::Yes);
                }
            }
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            if (buttons&ImRad::No)
            {
                //visible
                if (ImGui::Button("No", { 100*dp, 30*dp }))
                {
                    ClosePopup(ImRad::No);
                }
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
