// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "OpenFileActivity.h"
#include "MainActivity.h"
#include <filesystem>

OpenFileActivity openFileActivity;


void OpenFileActivity::Open()
{
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    if (ioUserData->activeActivity != "OpenFileActivity")
    {
        ioUserData->activeActivity = "OpenFileActivity";
        Init();
    }
}

void OpenFileActivity::Init()
{
    namespace chr = std::chrono;
    namespace fs = std::filesystem;
    std::error_code ec;
    files.clear();
    for (const auto& it : fs::directory_iterator(".", ec))
    {
        if (it.path().extension() != ".cpp")
            continue;
        int kb = (it.file_size() + 1023) / 1024;
        //auto cftime = chr::system_clock::to_time_t(chr::file_clock::to_sys(it.last_write_time()));
        auto lwt = it.last_write_time();
        time_t cftime = decltype(lwt)::clock::to_time_t(lwt);
        //std::string str = std::asctime(std::localtime(&cftime));
        //str.pop_back(); // rm the trailing '\n' put by asctime
        char buf[64];
        std::strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", std::localtime(&cftime));
        files.push_back({
            cftime,
            it.path().filename().string(),
            std::to_string(kb) + " KB",
            buf
        });
    }
    std::sort(files.begin(), files.end(), [](const auto& a, const auto& b) {
        return a.time > b.time;
    });
}

void OpenFileActivity::Draw()
{
    /// @style material
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    if (ioUserData->activeActivity != "OpenFileActivity")
        return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::SetNextWindowPos(ioUserData->WorkRect().Min);
    ImGui::SetNextWindowSize(ioUserData->WorkRect().GetSize()); //{ 400*dp, 700*dp }
    bool tmpOpen;
    if (ImGui::Begin("###OpenFileActivity", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin Child
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5*dp, 0 });
        ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
        ImGui::BeginChild("child1", { -1, 40*dp }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 5*dp, 0 });
            /// @separator

            /// @begin Button
            ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
            if (ImGui::Button("\xee\x97\x84", { 40*dp, -1 }))
            {
                OnClose();
            }
            ImGui::PopStyleColor();
            /// @end Button

            /// @begin Selectable
            ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
            ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0, 0.5f });
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImRad::Selectable("Open File", false, ImGuiSelectableFlags_DontClosePopups, { 0, -1 });
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
            /// @end Selectable

            /// @separator
            ImGui::PopStyleVar();
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        /// @end Child

        /// @begin Table
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, { 5*dp, 0 });
        ImRad::PushInvisibleScrollbar();
        if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_BordersInnerH, { -1, -1 }))
        {
            ImRad::ScrollWhenDragging(true);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch, 0);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 0*dp);
            ImGui::TableSetupColumn("Modified", ImGuiTableColumnFlags_WidthFixed, 0*dp);

            for (r = 0; r < files.size(); ++r)
            {
                ImGui::PushID(r);
                ImGui::TableNextRow(0, 0);
                ImGui::TableSetColumnIndex(0);
                /// @separator

                /// @begin Selectable
                ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0, 0.5f });
                if (ImRad::Selectable(ImRad::Format(" \xee\x89\x8d {}", files[r].name).c_str(), false, ImGuiSelectableFlags_DontClosePopups | ImGuiSelectableFlags_SpanAllColumns, { 0, 35*dp }))
                    OnSelect();
                ImGui::PopStyleVar();
                /// @end Selectable

                /// @begin Selectable
                ImRad::TableNextColumn(1);
                ImGui::BeginDisabled(true);
                ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0, 0.5f });
                ImRad::Selectable(ImRad::Format("{}", files[r].size).c_str(), false, ImGuiSelectableFlags_DontClosePopups, { 0, 35*dp });
                ImGui::PopStyleVar();
                ImGui::EndDisabled();
                /// @end Selectable

                /// @begin Selectable
                ImRad::TableNextColumn(1);
                ImGui::BeginDisabled(true);
                ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0, 0.5f });
                ImRad::Selectable(ImRad::Format("{}", files[r].modified).c_str(), false, ImGuiSelectableFlags_DontClosePopups, { 0, 35*dp });
                ImGui::PopStyleVar();
                ImGui::EndDisabled();
                /// @end Selectable


                /// @separator
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImRad::PopInvisibleScrollbar();
        ImGui::PopStyleVar();
        /// @end Table

        /// @separator
        ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    /// @end TopWindow
}

void OpenFileActivity::OnClose()
{
    mainActivity.Open();
}

void OpenFileActivity::OnSelect()
{
    if (r < 0 || r >= files.size())
        return;
    mainActivity.fileName = files[r].name;
    mainActivity.Open();
}
