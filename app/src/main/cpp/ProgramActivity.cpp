// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "ProgramActivity.h"
#include "MainActivity.h"
#include "cppdraw.h"

ProgramActivity programActivity;


void ProgramActivity::Open()
{
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    if (ioUserData->activeActivity != "ProgramActivity")
    {
        ioUserData->activeActivity = "ProgramActivity";
        Init();
    }
}

void ProgramActivity::Init()
{
    // TODO: Add your code here
}

void ProgramActivity::Draw()
{
    /// @style material
    /// @unit dp
    /// @begin TopWindow
    auto* ioUserData = (ImRad::IOUserData*)ImGui::GetIO().UserData;
    const float dp = ioUserData->dpiScale;
    if (ioUserData->activeActivity != "ProgramActivity")
        return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::SetNextWindowPos(ioUserData->WorkRect().Min);
    ImGui::SetNextWindowSize(ioUserData->WorkRect().GetSize()); //{ 400*dp, 700*dp }
    bool tmpOpen;
    if (ImGui::Begin("###ProgramActivity", &tmpOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin CustomWidget
        OnDraw({ -1, -1 });
        /// @end CustomWidget

        /// @begin Button
        ImGui::SetCursorScreenPos({ ImGui::GetCurrentWindow()->InnerRect.Max.x-37*dp, 10*dp }); //overlayPos
        ImGui::PushStyleColor(ImGuiCol_Text, 0xff7f817f);
        ImGui::PushStyleColor(ImGuiCol_Button, 0x00ffffff);
        if (ImGui::Button("\xee\x97\x8d", { 0, 0 }))
        {
            OnQuit();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        /// @end Button

        /// @separator
        ImGui::End();
    }
    ImGui::PopStyleVar();
    /// @end TopWindow
}

void ProgramActivity::OnQuit()
{
    mainActivity.Open();
}

//todo: compiled code
void draw(float time)
{
    color(RGB(255, 0, 255));
    line(0, 0, 200, 200);
}

void ProgramActivity::OnDraw(const ImRad::CustomWidgetArgs& args)
{
    touchDown_ = ImGui::IsMouseDown(0);
    touchPos_ = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
    color_ = 0xffffffff;
    thickness_ = 3.f;
    shapes_clear_();

    draw(0);

    auto* dl = ImGui::GetWindowDrawList();
    const Shape* shapes;
    size_t n = get_shapes_(&shapes);
    for (size_t i = 0; i < n; ++i)
    {
        const auto& sh = shapes[i];
        switch (sh.kind) {
            case Shape::Line:
                dl->AddLine({ sh.x1, sh.y1 }, { sh.x2, sh.y2 }, sh.fg, sh.thick);
                break;
        }
    }
}
