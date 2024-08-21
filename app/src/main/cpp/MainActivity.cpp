// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#include "MainActivity.h"
#include "InputQuery.h"
#include "MessageBox.h"
#include "OpenFileActivity.h"
#include "ProgramActivity.h"
#include "Guide.h"
#include "BuildOutput.h"
#include <filesystem>

namespace fs = std::filesystem;

MainActivity mainActivity;

extern void ShellExecute(const std::string& cmd, std::function<void(std::string_view)> clb = {});


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
    if (fileName == "") {
        textEdit.SetText("");
        return;
    }
    std::ifstream fin(fileName);
    if (!fin) {
        messageBox.buttons = ImRad::Ok;
        messageBox.message = "Can't read '" + fileName + "'";
        messageBox.OpenPopup();
        return;
    }
    std::string line;
    std::string content;
    while (std::getline(fin, line))
        content += line + "\n";
    if (!content.empty())
        content.pop_back();
    textEdit.SetText(content);

    using P = TextEditor::PaletteIndex;
    lightPalette = TextEditor::GetLightPalette();
    lightPalette[(int) P::CurrentLineFill] = 0x00000000;
    lightPalette[(int) P::Cursor] = TextEditor::GetRetroBluePalette()[(int) P::Cursor];
    lightPalette[(int) P::LineNumber] &= 0x7fffffff;
    lightPalette[(int) P::CurrentLineEdge] = 0xffe0e0e0;

    darkPalette = TextEditor::GetDarkPalette();
    darkPalette[(int) P::Cursor] = TextEditor::GetRetroBluePalette()[(int) P::Cursor];
    darkPalette[(int) P::LineNumber] &= 0x7fffffff;
    darkPalette[(int) P::Number] = TextEditor::GetLightPalette()[(int) P::Number];

    retroPalette = TextEditor::GetRetroBluePalette();
    retroPalette[(int) P::LineNumber] &= 0x8fffffff;
}

void MainActivity::Draw()
{
    /// @style material
    /// @unit dp
    if (startProgram) {
        startProgram = false;
        programActivity.Open();
    }
    
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    if (ioUserData->activeActivity != "MainActivity")
        return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 5*dp);
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
        guide.Draw();

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
            if (ImGui::MenuItem("Light Mode", "", &lightMode))
                OnLightMode();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("Dark Mode", "", &darkMode))
                OnDarkMode();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("Retro Mode", "", &retroMode))
                OnRetroMode();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("Increase Font Size", "", false))
                OnIncreaseSize();
            /// @end MenuIt

            /// @begin MenuIt
            if (ImGui::MenuItem("Decrease Font Size", "", false))
                OnDecreaseSize();
            /// @end MenuIt

            /// @begin MenuIt
            ImGui::Separator();
            if (ImGui::MenuItem("Copy All", "", false))
                OnCopyAll();
            /// @end MenuIt

            /// @separator
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        /// @end MenuIt

        /// @begin Child
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5*dp, 5*dp });
        ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
        ImGui::BeginChild("child1", { -1, 40*dp }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoSavedSettings);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 5*dp, -1*dp });
            /// @separator

            /// @begin Text
            hb21.BeginLayout();
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted(ImRad::Format(" {}", fileName).c_str());
            hb21.AddSize(0, ImRad::HBox::ItemSize);
            /// @end Text

            /// @begin Spacer
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImRad::Dummy({ hb21.GetSize(), 0 });
            hb21.AddSize(1, ImRad::HBox::Stretch(1));
            /// @end Spacer

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
            if (ImGui::Button("\xee\x83\xb0", { 35*dp, -1 }))
            {
                OnHelp();
            }
            hb21.AddSize(1, 35*dp);
            ImGui::PopStyleColor();
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
            if (ImGui::Button("\xee\x8b\x88", { 35*dp, -1 }))
            {
                ImRad::OpenWindowPopup("FileMenu");
            }
            hb21.AddSize(1, 35*dp);
            ImGui::PopStyleColor();
            /// @end Button

            /// @begin Button
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
            if (ImGui::Button("\xee\x97\x94", { 30*dp, -1 }))
            {
                ImRad::OpenWindowPopup("EditMenu");
            }
            hb21.AddSize(1, 30*dp);
            ImGui::PopStyleColor();
            /// @end Button

            /// @separator
            ImGui::PopStyleVar();
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        /// @end Child

        bool showButtons = !ImGui::GetTopMostAndVisiblePopupModal() && ioUserData->kbdShown;

        /// @begin CustomWidget
        OnEditor({ -1, showButtons?-40*dp:-1 });
        /// @end CustomWidget

        /// @begin Child
        if (showButtons)
        {
            //visible
            ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff663300);
            ImGui::BeginChild("child2", { -1, 40*dp }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoSavedSettings);
            {
                ImRad::ScrollWhenDragging(false);
                /// @separator

                /// @begin Button
                ImRad::Spacing(1);
                if (ImGui::Button("\xee\x8c\x9c", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("{", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("}", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("[", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("]", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("<", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button(">", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("|", { 36*dp, -1 }))
                {
                    OnButton();
                }
                if (ImGui::IsItemFocused())
                    OnButtonFocused();
                /// @end Button

                /// @begin Button
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                if (ImGui::Button("=", { 36*dp, -1 }))
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
    ImGui::PopStyleVar();
    /// @end TopWindow
}

void MainActivity::OnEditor(const ImRad::CustomWidgetArgs& args)
{
    if (fileName == "")
        return;

    float dp = ((ImRad::IOUserData *) ImGui::GetIO().UserData)->dpiScale;

    //render line numbers ourselves
    const TextEditor::Palette& palette = lightMode ? lightPalette : darkMode ? darkPalette : retroPalette;
    float charAdvanceY = ImGui::GetTextLineHeightWithSpacing(); /** mLineSpacing*/;
    auto lineNo = (int)floor(teScrollY / charAdvanceY);
    auto lineMax = std::max(0, std::min((int)textEdit.GetTotalLines() - 1, lineNo + (int)floor((teScrollY + teContentSizeY) / charAdvanceY)));

    ImGui::PushStyleColor(ImGuiCol_ChildBg, palette[(int)TextEditor::PaletteIndex::CurrentLineEdge]);
    ImGui::SetNextWindowScroll({ 0, teScrollY });
    float sizeX = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.f, "999").x + 2*dp;
    if (ImGui::BeginChild("lineNums", { sizeX, args.size.y }, 0, ImGuiWindowFlags_NoScrollbar))
    {
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGui::PushStyleColor(ImGuiCol_Text, palette[(int)TextEditor::PaletteIndex::LineNumber]);
        for (; lineNo <= lineMax; ++lineNo)
        {
            std::string str = std::to_string(lineNo + 1);
            ImVec2 ts = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.f, str.c_str());
            ImGui::GetWindowDrawList()->AddText({ pos.x + ImGui::GetWindowSize().x - ts.x - dp, pos.y + lineNo * charAdvanceY },
                                                textEdit.GetPalette()[(int)TextEditor::PaletteIndex::LineNumber],
                                                str.c_str());
        }
        ImGui::Dummy({ 1, textEdit.GetTotalLines() * charAdvanceY });
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::SameLine(0, 0);

    //need to keep it focused even when button is down (not pressed yet)
    if (setEditorFocus) {
        setEditorFocus = false;
        ImGui::SetNextWindowFocus();
    }
    textEdit.SetImGuiChildIgnored(true);
    textEdit.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
    textEdit.SetShowWhitespaces(false);
    textEdit.SetShowLineNumbers(false);
    textEdit.SetPalette(palette);
    ImRad::PushInvisibleScrollbar();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, textEdit.GetPalette()[(int)TextEditor::PaletteIndex::Background]);
    if (ImGui::BeginChild("textEdit", { -1, args.size.y }))
    {
        ImRad::ScrollWhenDragging(true);

        textEdit.Render("textEdit", args.size);
        teScrollY = ImGui::GetScrollY();
        teContentSizeY = ImGui::GetWindowContentRegionMax().y;

        //leave right margin so it's possible to click cursor after the last character on line
        ImGui::GetCurrentWindow()->ContentSize.x += 10 * dp;

        //put overlay button in the same window to make it work
        ImGui::SetCursorScreenPos({ImGui::GetCurrentWindow()->InnerRect.Max.x - 55 * dp,
                                   ImGui::GetCurrentWindow()->InnerRect.Max.y -
                                   51 * dp}); //overlayPos
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25 * dp);
        if (ImGui::Button("\xee\x80\xb7", {50 * dp, 50 * dp})) {
            OnRun();
        }
        ImGui::PopStyleVar();
        if (ImGui::IsWindowFocused() && !ImGui::IsItemFocused())
            ((ImRad::IOUserData *) ImGui::GetIO().UserData)->imeType = ImRad::ImeText;
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImRad::PopInvisibleScrollbar();
}

void MainActivity::OnButton()
{
    ImGuiID id = ImGui::GetItemID();
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    setEditorFocus = true;
    if (id == win->GetID("\uE31C"))
        textEdit.InsertText("\t");
    else if (id == win->GetID("{"))
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
    setEditorFocus = true;
}

void MainActivity::OnRun()
{
    SaveFile(fileName);
    buildOutput.output = { { BuildOutput::OutputRow::note, 0, 0, "Build has started..." } };
    buildOutput.OpenPopup();
    std::string cmd = "usr/bin/clang-18"
                      " --sysroot=" + fs::current_path().string() +
                      " -lc++ -lc++_shared -lm -Wall -o usr/tmp/prog.out" +
                      " usr/include/cppdraw.cpp " + fileName;
    ShellExecute(cmd, [this](std::string_view output) {
        int err = buildOutput.ParseOutput(output, fileName);
        if (!err) {
            //compiled OK
            system("chmod 777 usr/tmp/prog.out");
            buildOutput.ClosePopup();
            startProgram = true; //start from cpp thread not here
        }
    });
}

void MainActivity::OnFileNew()
{
    inputQuery.EnterFileName("New file name", [this](const std::string& fn) {
        NewFile(fn);
    });
}

void MainActivity::OnFileSaveAs()
{
    inputQuery.EnterFileName("New file name", [this](const std::string& fn) {
        SaveFile(fn);
    });
}

void MainActivity::OnFileOpen()
{
    if (fileName != "")
        SaveFile(fileName);
    openFileActivity.Open();
}

void MainActivity::OnFileDelete()
{
    messageBox.buttons = ImRad::Yes | ImRad::No;
    messageBox.message = "Really delete '" + fileName + "'?";
    messageBox.OpenPopup([this](ImRad::ModalResult mr) {
        if (mr == ImRad::Yes) {
            std::error_code ec;
            fs::remove(fileName, ec);
            if (ec) {
                messageBox.buttons = ImRad::Ok;
                messageBox.message = "Error: can't remove '" + fileName + "'";
                messageBox.OpenPopup();
                return;
            }
            fileName = "";
        }
    });
}

void MainActivity::OnLightMode()
{
    lightMode = true;
    retroMode = darkMode = false;
}

void MainActivity::OnDarkMode()
{
    darkMode = true;
    retroMode = lightMode = false;
}

void MainActivity::OnRetroMode()
{
    retroMode = true;
    lightMode = darkMode = false;
}

void MainActivity::OnIncreaseSize()
{
}

void MainActivity::OnDecreaseSize()
{
}

void MainActivity::OnHelp()
{
    guide.OpenPopup();
}

void MainActivity::OnCopyAll()
{
    ImGui::SetClipboardText(textEdit.GetText().c_str());
}

void MainActivity::NewFile(const std::string& fname)
{
    const char* SRC_TEMPLATE =
            "#include \"cppdraw.h\"\n\n"
            "void draw()\n{\n"
            "\tcolor(mouseDown() ? 0xff0000ff : 0xff00ff00);\n"
            "\tfillRect(100, 100, 400, 300);\n"
            "}\n";
    textEdit.SetText(SRC_TEMPLATE);
    SaveFile(fname);
}

void MainActivity::SaveFile(const std::string& fname)
{
    std::string path = fname;
    if (fname.find(".") == std::string::npos)
        path += ".cpp";
    std::ofstream fout(path);
    if (!fout) {
        messageBox.buttons = ImRad::Ok;
        messageBox.message = "Error: can't write in '" + path + "'";
        messageBox.OpenPopup();
        return;
    }
    fout << textEdit.GetText();
    fileName = path;
}

void MainActivity::GoTo(int line, int column)
{
    if (line >= 1)
        textEdit.SetCursorPosition({ line - 1, column - 1 });
}

void MainActivity::ResetLayout()
{
    // ImGui::GetCurrentWindow()->HiddenFramesCannotSkipItems = 2;
    hb21.Reset();
}
