#include "cppdraw.h"
#include <vector>
//#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

DrawCmd cmd;
ucolor color_;
float thickness_;
//std::string fontName_;
float fontSize_;
std::vector<Shape> shapes_;
std::vector<char> strBuffer_;

void newFrame()
{
    color_ = 0xffffffff;
    thickness_ = 3.f;
    //fontName_ = "";
    fontSize_ = 18;
    shapes_.clear();
    strBuffer_.clear();
}

Shape::Shape(Kind k)
: kind(k)
{}

ucolor RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

float time()
{
    return cmd.time;
}

float timeDelta()
{
    return cmd.timeDelta;
}

DateTime dateTime()
{
    return cmd.dateTime;
}

vec2 screenSize()
{
    return cmd.screenSize;
}

bool mouseDown(int)
{
    return cmd.mouseDown;
}

vec2 mousePos()
{
    return cmd.mousePos;
}

vec2 mouseDelta()
{
    return cmd.mouseDelta;
}

bool keyPressed(int key)
{
    if (key < 0 || key >= std::size(cmd.keys))
        return false;
    return cmd.keys[key];
}

void color(ucolor c)
{
    color_ = c;
}

void thickness(float th)
{
    thickness_ = th;
}

void font(ZStringView name, float fontSize)
{
    fontSize_ = fontSize;
}

void line(float x1, float y1, float x2, float y2)
{
    Shape sh(Shape::Line);
    sh.l.x1 = x1;
    sh.l.y1 = y1;
    sh.l.x2 = x2;
    sh.l.y2 = y2;
    sh.l.color = color_;
    sh.l.thick = thickness_;
    shapes_.push_back(sh);
}

void rectangle(float x1, float y1, float x2, float y2)
{
    Shape sh(Shape::Rect);
    sh.r.x1 = x1;
    sh.r.y1 = y1;
    sh.r.x2 = x2;
    sh.r.y2 = y2;
    sh.r.color = color_;
    sh.r.thick = thickness_;
    shapes_.push_back(sh);
}

void fillRect(float x1, float y1, float x2, float y2)
{
    Shape sh(Shape::FillRect);
    sh.r.x1 = x1;
    sh.r.y1 = y1;
    sh.r.x2 = x2;
    sh.r.y2 = y2;
    sh.r.color = color_;
    shapes_.push_back(sh);
}

void fillRectWH(float x1, float y1, float w, float h)
{
    fillRect(x1, y1, x1+w, y1+h);
}

void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    Shape sh(Shape::FillTriangle);
    sh.t.x1 = x1;
    sh.t.y1 = y1;
    sh.t.x2 = x2;
    sh.t.y2 = y2;
    sh.t.x3 = x3;
    sh.t.y3 = y3;
    sh.t.color = color_;
    shapes_.push_back(sh);
}

void fillQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    fillTriangle(x1, y1, x2, y2, x3, y3);
    fillTriangle(x3, y3, x4, y4, x1, y1);
}

void circle(float x1, float y1, float r)
{
    Shape sh(Shape::Circle);
    sh.c.x1 = x1;
    sh.c.y1 = y1;
    sh.c.r = r;
    sh.c.color = color_;
    sh.c.thick = thickness_;
    shapes_.push_back(sh);
}

void fillCircle(float x1, float y1, float r)
{
    Shape sh(Shape::FillCircle);
    sh.c.x1 = x1;
    sh.c.y1 = y1;
    sh.c.r = r;
    sh.c.color = color_;
    shapes_.push_back(sh);
}

void text(float x, float y, ZStringView text)
{
    Shape sh(Shape::Text);
    sh.x.x1 = x;
    sh.x.y1 = y;
    sh.x.color = color_;
    sh.x.text = strBuffer_.size();
    strBuffer_.insert(strBuffer_.end(), text.begin(), text.end() + 1);
    sh.x.font = 0;
    sh.x.size = fontSize_;
    shapes_.push_back(sh);
}

void playSound(ZStringView path)
{
    Shape sh(Shape::Sound);
    sh.s.path = strBuffer_.size();
    strBuffer_.insert(strBuffer_.end(), path.begin(), path.end() + 1);
    shapes_.push_back(sh);
}

int main()
{
    strBuffer_.reserve(1024 * 1024);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stdout, "can't create socket (%d)\n", errno);
        return 1;
    }
    sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(CPPDRAW_PORT);
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable))) {
        fprintf(stdout, "can't setsockopt (%d)\n", errno);
        return 2;
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stdout, "can't bind (%d)\n", errno);
        return 2;
    }
    if (listen(sockfd, 5) < 0) {
        fprintf(stdout, "can't listen (%d)\n", errno);
        return 2;
    }
    fprintf(stdout, "listening...\n"); //important to use \n
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        fprintf(stdout, "can't accept (%d)\n", errno);
        return 3;
    }
    fprintf(stdout, "connection accepted\n");
    while (true) {
        char buffer[256];
        int n = read(newsockfd, buffer, sizeof(buffer));
        if (n != sizeof(DrawCmd)) {
            fprintf(stdout, "read error\n");
            break;
        }
        cmd = *(const DrawCmd*)buffer;

        newFrame();
        draw();

        uint32_t num = htonl(strBuffer_.size());
        n = write(newsockfd, (void*)&num, 4);
        if (n < 0) {
            fprintf(stdout, "write error\n");
            break;
        }
        n = write(newsockfd, strBuffer_.data(), strBuffer_.size());
        if (n < 0) {
            fprintf(stdout, "write error\n");
            break;
        }
        num = htonl(shapes_.size());
        n = write(newsockfd, (void*)&num, 4);
        if (n < 0) {
            fprintf(stdout, "write error\n");
            break;
        }
        n = write(newsockfd, shapes_.data(), shapes_.size() * sizeof(Shape));
        if (n < 0) {
            fprintf(stdout, "write error\n");
            break;
        }

    }

    close(newsockfd);
    close(sockfd);
    return 0;
}