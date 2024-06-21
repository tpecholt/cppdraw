// Generated with ImRAD 0.7
// visit https://github.com/tpecholt/imrad

#include "ProgramActivity.h"
#include "MainActivity.h"
#include "cppdraw.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

ProgramActivity programActivity;

extern void StartDeamon(const std::string& cmd, std::function<void(int)> clb);
extern void StopDeamon();

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
    StartDeamon("usr/tmp/prog.out", [this](int pid) {
        Connect();
    });
}

void ProgramActivity::Connect()
{
    if (!sockfd)
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        sockfd = 0;
        error = "can't socket";
        return;
    }
    error = "connecting...";
    sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CPPDRAW_PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        close(sockfd);
        sockfd = 0;
        error = "can't connect";
        return;
    }
    error = "";
    timeStart = ImGui::GetTime();
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
        if (ImGui::IsKeyPressed(ImGuiKey_AppBack))
            OnQuit();
        /// @separator

        // TODO: Add Draw calls of dependent popup windows here

        /// @begin CustomWidget
        OnDraw({ -1, -1 });
        /// @end CustomWidget

        /// @separator
        ImGui::End();
    }
    ImGui::PopStyleVar();
    /// @end TopWindow
}

void ProgramActivity::OnQuit()
{
    if (sockfd) {
        close(sockfd);
        sockfd = 0;
    }
    mainActivity.Open();
}

void ProgramActivity::OnDraw(const ImRad::CustomWidgetArgs& args)
{
    if (error != "")
        ImGui::TextDisabled("%s", error.c_str());
    if (!sockfd)
        return;

    DrawCmd dcmd;
    dcmd.screenSize = { ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y };
    dcmd.time = ImGui::GetTime() - timeStart;
    dcmd.touchDown = ImGui::IsMouseDown(0);
    dcmd.touchPos = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };
    int n = write(sockfd, &dcmd, sizeof(DrawCmd));
    if (n != sizeof(DrawCmd))
        return;

    buf.resize(4);
    n = read(sockfd, buf.data(), 4);
    if (n != 4)
        return;
    int num = ntohl(*(uint32_t*)buf.data());
    strBuf.resize(num);
    int off = 0;
    while (num > 0)
    {
        int to_read = 10*1024;
        if (to_read > num)
            to_read = num;
        n = read(sockfd, strBuf.data() + off, to_read);
        off += n;
        num -= n;
    }

    n = read(sockfd, buf.data(), 4);
    if (n != 4)
        return;
    num = ntohl(*(uint32_t*)buf.data());
    int len = num * sizeof(Shape);
    buf.resize(len);
    off = 0;
    while (len > 0)
    {
        int to_read = 10*1024;
        if (to_read > len)
            to_read = len;
        n = read(sockfd, buf.data() + off, to_read);
        len -= n;
        int nsh = (off + n) / sizeof(Shape);
        if (!nsh) {
            off += n;
            continue;
        }

        auto *dl = ImGui::GetWindowDrawList();
        const Shape *shapes = (const Shape *)buf.data();
        for (size_t i = 0; i < nsh; ++i) {
            const auto &sh = shapes[i];
            switch (sh.kind) {
                case Shape::Line:
                    dl->AddLine({ sh.l.x1, sh.l.y1 }, { sh.l.x2, sh.l.y2 }, sh.l.color, sh.l.thick);
                    break;
                case Shape::Rect:
                    dl->AddRect({ sh.r.x1, sh.r.y1 }, { sh.r.x1+sh.r.w, sh.r.y1+sh.r.h }, sh.l.color, 0, 0, sh.l.thick);
                    break;
                case Shape::FillRect:
                    dl->AddRectFilled({ sh.r.x1, sh.r.y1 }, { sh.r.x1+sh.r.w, sh.r.y1+sh.r.h }, sh.l.color);
                    break;
                case Shape::Circle:
                    dl->AddCircle({ sh.c.x1, sh.c.y1 }, sh.c.r, sh.l.color, 0, sh.l.thick);
                    break;
                case Shape::Text:
                    dl->AddText({ sh.t.x1, sh.t.y1 }, sh.t.color, strBuf.data() + sh.t.text);
                    break;
            }
        }

        //copy unfinished Shape to front
        off = (off + n) % sizeof(Shape);
        memcpy(buf.data(), buf.data() + nsh * sizeof(Shape), off);
    }
}
