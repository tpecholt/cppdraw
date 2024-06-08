// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "MainActivity.h"
#include "InputQuery.h"
#include "MessageBox.h"
#include <filesystem>

namespace fs = std::filesystem;

MainActivity mainActivity;


void MainActivity::Open()
{
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    if (ioUserData->activeActivity != "MainActivity")
    {
        ioUserData->activeActivity = "MainActivity";
        Init();
    }
}

void MainActivity::Init()
{
    // TODO: Add your code here
}

void MainActivity::Draw()
{
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    if (ioUserData->activeActivity != "MainActivity")
        return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::SetNextWindowPos(ioUserData->WorkRect().Min);
    ImGui::SetNextWindowSize(ioUserData->WorkRect().GetSize()); //{ 400*dp, 700*dp }
    bool tmpOpen;
    if (ImGui::Begin("###MainActivity", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here
        inputQuery.Draw();
        messageBox.Draw();

        /// @begin MenuIt
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { -1*dp, 20*dp });
        if (ImGui::BeginPopup("FileMenu", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings))
        {
            /// @separator

            /// @begin MenuIt
            if (ImGui::MenuItem("\xee\x89\x8d New...", "", false))
                OnFileNew();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("\xee\x8b\x88 Open...", "", false))
                OnFileOpen();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("\xee\x85\xa1 Save As...", "", false))
                OnFileSaveAs();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("\xee\x97\x8d Delete...", "", false))
                OnFileDelete();
            /// @end MenuIt

            /// @separator
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        /// @end MenuIt

        /// @begin MenuIt
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 10*dp });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { -1*dp, 20*dp });
        if (ImGui::BeginPopup("EditMenu", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings))
        {
            /// @separator

            /// @begin MenuIt
            ImGui::MenuItem("Dark Mode", "", &darkMode);
            /// @end MenuIt

            /// @begin MenuIt
            ImGui::MenuItem("Retro Mode", "", &retroMode);
            /// @end MenuIt

            /// @begin MenuIt
            ImGui::Separator();
            ImGui::MenuItem("Copy All", "", false);
            /// @end MenuIt

            /// @begin MenuIt
            ImGui::MenuItem("Paste All", "", false);
            /// @end MenuIt

            /// @separator
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        /// @end MenuIt

        /// @begin Child
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10*dp, 5*dp });
        ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
        ImGui::BeginChild("child1", { -1, 40*dp }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoSavedSettings);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 5*dp, -1*dp });
            /// @separator

            /// @begin Table
            if (ImGui::BeginTable("table2", 2, ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_NoPadInnerX, { -1, 0 }))
            {
                ImGui::TableSetupColumn("left-content", ImGuiTableColumnFlags_WidthStretch, 0);
                ImGui::TableSetupColumn("right-content", ImGuiTableColumnFlags_WidthFixed, 0*dp);
                ImGui::TableNextRow(0, 0);
                ImGui::TableSetColumnIndex(0);
                /// @separator

                /// @begin Text
                ImGui::AlignTextToFramePadding();
                ImGui::TextUnformatted(ImRad::Format("{}", fileName).c_str());
                /// @end Text

                /// @begin Button
                ImRad::TableNextColumn(1);
                ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
                if (ImGui::Button("\xee\x8b\x88", { 40*dp, -1 }))
                {
                    ImRad::OpenWindowPopup("FileMenu");
                }
                ImGui::PopStyleColor();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
                if (ImGui::Button("\xee\x97\x94", { 40*dp, -1 }))
                {
                    ImRad::OpenWindowPopup("EditMenu");
                }
                ImGui::PopStyleColor();
                /// @end Button


                /// @separator
                ImGui::EndTable();
            }
            /// @end Table

            /// @separator
            ImGui::PopStyleVar();
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        /// @end Child

        /// @begin CustomWidget
        OnEditor({ -1, -40*dp });
        /// @end CustomWidget

        /// @begin Child
        if (ioUserData->kbdShown && !ImGui::GetTopMostAndVisiblePopupModal())
        {
            //visible
            ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff663300);
            ImGui::BeginChild("child3", { -1, 40*dp }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoSavedSettings);
            {
                ImRad::ScrollWhenDragging(false);
                /// @separator

                /// @begin Button
                if (ImGui::Button("{", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("}", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("[", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("]", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("<", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button(">", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("|", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("=", { 40*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
        }
        /// @end Child

        /// @separator
        ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    /// @end TopWindow
}

void MainActivity::OnEditor(const ImRad::CustomWidgetArgs& args)
{
    //need to keep it focused even when button is down (not pressed yet)
    if (setFocus) {
        setFocus = false;
        ImGui::SetNextWindowFocus();
    }

    ImGui::BeginChild("textEdit", args.size);

    textEdit.SetImGuiChildIgnored(true);
    textEdit.SetPalette(darkMode ? TextEditor::GetDarkPalette() : TextEditor::GetRetroBluePalette());
    textEdit.Render("textEdit", args.size);

    if (ImGui::IsWindowFocused())
        ((ImRad::IOUserData*)ImGui::GetIO().UserData)->imeType = ImRad::ImeText;

    //put overlay button in the same window to make it work
    float dp = ((ImRad::IOUserData*)ImGui::GetIO().UserData)->dpiScale;
    ImGui::SetCursorScreenPos({ ImGui::GetCurrentWindow()->InnerRect.Max.x-55*dp, ImGui::GetCurrentWindow()->InnerRect.Max.y-51*dp }); //overlayPos
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25*dp);
    if (ImGui::Button("\xee\x80\xb7", { 50*dp, 50*dp }))
    {
        OnRun();
    }
    ImGui::PopStyleVar();

    ImGui::EndChild();
}

void MainActivity::OnButton()
{
    ImGuiID id = ImGui::GetItemID();
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    setFocus = true;
    if (id == win->GetID("{"))
        textEdit.InsertText("{");
    else if (id == win->GetID("}"))
        textEdit.InsertText("}");
    else if (id == win->GetID("["))
        textEdit.InsertText("[");
    else if (id == win->GetID("]"))
        textEdit.InsertText("]");
    else if (id == win->GetID("<"))
        textEdit.InsertText("<");
    else if (id == win->GetID(">"))
        textEdit.InsertText(">");
    else if (id == win->GetID("|"))
        textEdit.InsertText("|");
    else if (id == win->GetID("="))
        textEdit.InsertText("=");
}

void MainActivity::OnButtonFocused()
{
    setFocus = true;
}

void MainActivity::OnRun()
{
    fileName = fileName + "R";
}

void MainActivity::OnFileNew()
{
    inputQuery.label = "Enter file name:";
    inputQuery.value = "";
    inputQuery.OpenPopup([this](ImRad::ModalResult) {
        if (fs::exists(homeDir + "/" + inputQuery.value)) {
            messageBox.message = "'" + inputQuery.value + "' already exists. Overwrite?";
            messageBox.OpenPopup([this](ImRad::ModalResult) {
                DoNewFile(inputQuery.value);
            });
        }
        else {
            DoNewFile(inputQuery.value);
        }
    });
}

void MainActivity::OnFileSaveAs()
{
    inputQuery.label = "Enter file name:";
    inputQuery.value = "";
    inputQuery.OpenPopup([this](ImRad::ModalResult) {
        if (fs::exists(homeDir + "/" + inputQuery.value)) {
            messageBox.message = "'" + inputQuery.value + "' already exists. Overwrite?";
            messageBox.OpenPopup([this](ImRad::ModalResult) {
                DoSaveAs(inputQuery.value);
            });
        }
        else {
            DoSaveAs(inputQuery.value);
        }
    });
}

void MainActivity::OnFileOpen()
{
}

void MainActivity::OnFileDelete()
{
}

void MainActivity::DoNewFile(const std::string& fname)
{
    fileName = fname;
}

void MainActivity::DoSaveAs(const std::string& fname)
{
    fileName = fname;
}