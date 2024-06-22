#include "cppdraw.h"
#include <vector>
//#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

clr color_;
float thickness_;
//std::string fontName_;
float fontSize_;
float time_;
int touchDown_;
vec2 touchPos_;
vec2 screenSize_;

std::vector<Shape> shapes_;
std::vector<char> strBuffer_;

Shape::Shape(Kind k)
: kind(k)
{}

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

float time()
{
    return time_;
}

vec2 screenSize()
{
    return screenSize_;
}

bool touchDown()
{
    return touchDown_;
}

vec2 touchPos()
{
    return touchPos_;
}

void color(clr c)
{
    color_ = c;
}

void thickness(float th)
{
    thickness_ = th;
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

void rectangle(float x1, float y1, float w, float h)
{
    Shape sh(Shape::Rect);
    sh.r.x1 = x1;
    sh.r.y1 = y1;
    sh.r.w = w;
    sh.r.h = h;
    sh.r.color = color_;
    sh.r.thick = thickness_;
    shapes_.push_back(sh);
}

void fillRect(float x1, float y1, float w, float h)
{
    Shape sh(Shape::FillRect);
    sh.r.x1 = x1;
    sh.r.y1 = y1;
    sh.r.w = w;
    sh.r.h = h;
    sh.r.color = color_;
    shapes_.push_back(sh);
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

int main()
{
    strBuffer_.reserve(1024 * 1024);
    FILE* vole = fopen("vole.txt", "w");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(vole, "can't socket"); fclose(vole);
        fprintf(stdout, "can't create socket (%d)\n", errno);
        return 1;
    }
    sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(CPPDRAW_PORT);
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable))) {
        fprintf(vole, "can't setsockopt"); fclose(vole);
        fprintf(stdout, "can't setsockopt (%d)\n", errno);
        return 2;
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(vole, "can't bind"); fclose(vole);
        fprintf(stdout, "can't bind (%d)\n", errno);
        return 2;
    }
    if (listen(sockfd, 5) < 0) {
        fprintf(vole, "can't listen"); fclose(vole);
        fprintf(stdout, "can't listen (%d)\n", errno);
        return 2;
    }
    fprintf(vole, "listening\n"); fflush(vole);
    fprintf(stdout, "listening...\n"); //important to use \n
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        fprintf(stdout, "can't accept (%d)\n", errno);
        return 3;
    }
    fprintf(vole, "accepted\n"); fflush(vole);
    fprintf(stdout, "connection accepted\n");
    while (true) {
        char buffer[256];
        int n = read(newsockfd, buffer, sizeof(buffer));
        if (n != sizeof(DrawCmd)) {
            fprintf(vole, "read error\n");
            fflush(vole);
            break;
        }
        const DrawCmd* dcmd = (const DrawCmd*)buffer;
        screenSize_ = dcmd->screenSize;
        time_ = dcmd->time;
        touchDown_ = dcmd->touchDown;
        touchPos_ = dcmd->touchPos;
        color_ = 0xffffffff;
        thickness_ = 3.f;
        //fontName_ = "";
        fontSize_ = 18;
        shapes_.clear();
        strBuffer_.clear();

        draw();

        uint32_t num = htonl(strBuffer_.size());
        n = write(newsockfd, (void*)&num, 4);
        if (n < 0) {
            fprintf(vole, "write error\n");
            break;
        }
        n = write(newsockfd, strBuffer_.data(), strBuffer_.size());
        if (n < 0) {
            fprintf(vole, "write error\n");
            break;
        }
        num = htonl(shapes_.size());
        n = write(newsockfd, (void*)&num, 4);
        if (n < 0) {
            fprintf(vole, "write error\n");
            break;
        }
        n = write(newsockfd, shapes_.data(), shapes_.size() * sizeof(Shape));
        if (n < 0) {
            fprintf(vole, "write error\n");
            break;
        }

    }

    close(newsockfd);
    close(sockfd);
    fprintf(vole, "finished!\n");
    fclose(vole);
    return 0;
}