// Generated with ImRAD 0.8
// visit https://github.com/tpecholt/imrad

#include "BuildOutput.h"
#include "MainActivity.h"

BuildOutput buildOutput;


void BuildOutput::OpenPopup()
{
    modalResult = ImRad::None;
    animator.StartAlways(&animPos.y, -ImGui::GetMainViewport()->Size.y / 2.f, 0.f, ImRad::Animator::DurOpenPopup);
    ImGui::OpenPopup(ID);
    Init();
}

void BuildOutput::ClosePopup()
{
    modalResult = ImRad::Cancel;
    animator.StartOnce(&animPos.y, animPos.x, -animator.GetWindowSize().y, ImRad::Animator::DurClosePopup);
}

void BuildOutput::Init()
{
    // TODO: Add your code here
}

void BuildOutput::Draw()
{
    /// @style material
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    ID = ImGui::GetID("###BuildOutput");
    ImGui::PushStyleColor(ImGuiCol_PopupBg, 0xff323432);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 10*dp });
    ImGui::SetNextWindowPos({ ioUserData->WorkRect().Max.x - animPos.x, ioUserData->WorkRect().Max.y - animPos.y }, 0, { 1, 1 });  //Bottom
    ImGui::SetNextWindowSize({ ioUserData->WorkRect().GetWidth(), 400*dp }); //{ 420*dp, 400*dp }
    if (ImGui::BeginPopup("title###BuildOutput", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        animator.Tick();
        if (!ImRad::MoveWhenDragging(ImGuiDir_Down, animPos, ioUserData->dimBgRatio))
            ClosePopup();
        ImRad::RenderFilledWindowCorners(ImDrawFlags_RoundCornersBottom);
        if (modalResult != ImRad::None && animator.IsDone())
        {
            ImGui::CloseCurrentPopup();
        }
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin Table
        if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_NoPadInnerX, { -1, 0 }))
        {
            ImGui::TableSetupColumn("left-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableSetupColumn("content", ImGuiTableColumnFlags_WidthFixed, 60*dp);
            ImGui::TableSetupColumn("right-stretch", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableNextRow(0, 0);
            ImGui::TableSetColumnIndex(0);
            /// @separator

            /// @begin Separator
            ImRad::TableNextColumn(1);
            ImRad::Spacing(1);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal, 3*dp);
            /// @end Separator


            /// @separator
            ImGui::EndTable();
        }
        /// @end Table

        newSel = -1;
        /// @begin Table
        ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff000000);
        ImRad::PushInvisibleScrollbar();
        if (ImGui::BeginTable("table2", 1, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_ScrollY, { -1, -1 }))
        {
            ImRad::ScrollWhenDragging(true);
            ImGui::TableSetupColumn("A", ImGuiTableColumnFlags_WidthStretch, 0);

            for (int i = 0; i < output.size(); ++i)
            {
                ImGui::PushID(i);
                ImGui::TableNextRow(0, 40*dp);
                ImGui::TableSetColumnIndex(0);
                /// @separator

                /// @begin Text
                ImGui::PushStyleColor(ImGuiCol_Text, 0xffc2c2c2);
                ImGui::TextUnformatted(ImRad::Format("{} ", output[i].kind==2?"\xee\x80\x80":output[i].kind==1?"\xee\x80\x82":"\xee\x83\x89").c_str());
                ImGui::PopStyleColor();
                /// @end Text

                /// @begin Text
                ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
                ImGui::PushStyleColor(ImGuiCol_Text, output[i].kind==2?0xff6060ff:output[i].kind==1?0xff4080ff:0xffc2c2c2);
                ImGui::PushTextWrapPos(0);
                ImGui::TextUnformatted(ImRad::Format("{}", output[i].text).c_str());
                ImGui::PopTextWrapPos();
                ImGui::PopStyleColor();
                if (ImGui::IsItemHovered())
                    OnItemHovered();
                /// @end Text


                /// @separator
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::PopStyleColor();
        ImRad::PopInvisibleScrollbar();
        /// @end Table

        sel = newSel;
        
        /// @separator
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    /// @end TopWindow
        sel = newSel;
        
        sel = newSel;
        
        sel = newSel;
        
}

int BuildOutput::ParseOutput(std::string_view str, std::string_view fname)
{
    int err = 0;
    int beg = 0;
    output.clear();
    while (!str.empty())
    {
        auto end = str.find(fname, beg);
        std::string_view tmp = str.substr(beg, end == std::string::npos ? end : end - beg);
        if (!tmp.empty() && output.empty()) {
            output.push_back({});
            ++err;
        }
        output.back().text += tmp;
        if (end == std::string::npos)
            break;
        int i = end + fname.size();
        if (i >= str.size() || str[i] != ':') {
            if (!output.empty())
                output.back().text += str.substr(end, i - end);
            beg = i;
            continue;
        }
        int line = 0;
        for (++i; i < str.size() && isdigit(str[i]); ++i)
            line = line * 10 + str[i] - '0';
        if (i == str.size() || str[i] != ':') {
            if (!output.empty())
                output.back().text += str.substr(end, i - end);
            beg = i;
            continue;
        }
        int col = 0;
        for (++i; i < str.size() && isdigit(str[i]); ++i)
            col = col * 10 + str[i] - '0';
        if (i + 1 >= str.size() || str[i] != ':' || str[i + 1] != ' ') {
            if (!output.empty())
                output.back().text += str.substr(end, i - end);
            beg = i;
            continue;
        }
        i += 2;
        output.push_back({});
        output.back().line = line;
        output.back().column = col;
        output.back().text = str.substr(end, i - end);
        output.back().kind = OutputRow::note;
        if (!str.compare(i, 7, "warning"))
            output.back().kind = OutputRow::warning;
        if (!str.compare(i, 5, "error")) {
            output.back().kind = OutputRow::error;
            ++err;
        }
        beg = i;
    }
    return err;
}

void BuildOutput::OnBeginRow()
{
    if (ImGui::TableGetRowIndex() == sel)
        ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImGuiCol_ButtonActive));
}

void BuildOutput::OnItemHovered()
{
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        newSel = ImGui::TableGetRowIndex();
        mainActivity.GoTo(output[newSel].line, output[newSel].column);
    }
}

