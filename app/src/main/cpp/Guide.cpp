// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "Guide.h"
#include "imgui_markdown/imgui_markdown.h"

Guide guide;

extern int GetAssetData(const char* filename, void** outData);

void Guide::OpenPopup(std::function<void(ImRad::ModalResult)> clb)
{
    callback = clb;
    modalResult = ImRad::None;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    animator.StartAlways(&animPos.y, -ImGui::GetMainViewport()->Size.y / 2.f, 0.f, ImRad::Animator::DurOpenPopup);
    animator.StartAlways(&ioUserData->dimBgRatio, 0.f, 1.f, ImRad::Animator::DurOpenPopup);
    ImGui::OpenPopup(ID);
    Init();
}

void Guide::ClosePopup(ImRad::ModalResult mr)
{
    modalResult = mr;
    auto *ioUserData = (ImRad::IOUserData *)ImGui::GetIO().UserData;
    animator.StartOnce(&animPos.y, animPos.x, -animator.GetWindowSize().y, ImRad::Animator::DurClosePopup);
    animator.StartOnce(&ioUserData->dimBgRatio, ioUserData->dimBgRatio, 0.f, ImRad::Animator::DurClosePopup);
}

void Guide::Init()
{
    void* data = nullptr;
    int size = GetAssetData("guide.md", &data);
    if (data) {
        content.assign((char*)data, size);
    }
}

void Guide::Draw()
{
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    ID = ImGui::GetID("###Guide");
    ImGui::PushStyleColor(ImGuiCol_PopupBg, 0xff323432);
    ImGui::SetNextWindowPos({ ioUserData->WorkRect().Max.x - animPos.x, ioUserData->WorkRect().Max.y - animPos.y }, 0, { 1, 1 });  //Bottom
    ImGui::SetNextWindowSize({ ioUserData->WorkRect().GetWidth(), 500*dp }); //{ 420*dp, 500*dp }
    bool tmpOpen = true;
    if (ImGui::BeginPopupModal("title###Guide", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse))
    {
        animator.Tick();
        if (!ImRad::MoveWhenDragging(ImGuiDir_Down, animPos, ioUserData->dimBgRatio))
            ClosePopup();
        ImRad::RenderDimmedBackground(ioUserData->WorkRect(), ioUserData->dimBgRatio);
        if (modalResult != ImRad::None && animator.IsDone())
        {
            ImGui::CloseCurrentPopup();
            if (modalResult != ImRad::Cancel)
                callback(modalResult);
        }
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin CustomWidget
        OnGuide({ -1, -1 });
        /// @end CustomWidget

        /// @separator
        ImGui::EndPopup();
    }
    ImGui::PopStyleColor();
    /// @end TopWindow
}

void Guide::OnGuide(const ImRad::CustomWidgetArgs& args)
{
    ImGui::MarkdownConfig cfg;
    const auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    cfg.separatorThickness = 3 * ioUserData->dpiScale;
    cfg.headingFormats[0] = { ImRad::GetFontByName("H1"), true };
    cfg.headingFormats[1] = { ImRad::GetFontByName("H2"), true };
    cfg.headingFormats[2] = { ImRad::GetFontByName("H3"), false };

    ImRad::PushInvisibleScrollbar();
    ImGui::BeginChild("md", args.size);
    if (ImGui::IsWindowAppearing())
        ImGui::SetScrollY(0);

    ImRad::ScrollWhenDragging(true);
    ImGui::Markdown(content.c_str(), content.size(), cfg);

    ImGui::EndChild();
    ImRad::PopInvisibleScrollbar();
}
