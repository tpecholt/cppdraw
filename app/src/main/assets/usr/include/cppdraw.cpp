#include "cppdraw.h"
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

clr color_;
clr bkcolor_;
float thickness_;
int touchDown_;
vec2 touchPos_;
vec2 screenSize_;

static std::vector<Shape> shapes_;

Shape::Shape(Kind k)
: kind(k), fg(color_), bg(), thick(thickness_)
{}

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

void color(clr c)
{
    color_ = c;
}

void line(float x1, float y1, float x2, float y2)
{
    Shape line(Shape::Line);
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    shapes_.push_back(line);
}

int main()
{
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
        return 2;
        fprintf(stdout, "can't setsockopt (%d)\n", errno);
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stdout, "can't bind (%d)\n", errno);
        return 2;
    }
    if (listen(sockfd, 5) < 0) {
        fprintf(stdout, "can't listen (%d)\n", errno);
        return 2;
    }
    printf("listening...\n"); //important to use \n
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        fprintf(stdout, "can't accept (%d)\n", errno);
        return 3;
    }

    while (true) {
        char buffer[256];
        int n = read(newsockfd, buffer, sizeof(buffer));
        if (n != sizeof(DrawCmd))
            break;
        const DrawCmd* dcmd = (const DrawCmd*)buffer;
        screenSize_ = dcmd->screenSize;
        touchDown_ = dcmd->touchDown;
        touchPos_ = dcmd->touchPos;
        color_ = 0xffffffff;
        bkcolor_ = 0x0;
        thickness_ = 3.f;
        shapes_.clear();

        draw(dcmd->time);

        uint32_t ss = htonl(shapes_.size());
        n = write(newsockfd, (void*)&ss, 4);
        if (n < 0)
            break;
        n = write(newsockfd, shapes_.data(), shapes_.size() * sizeof(Shape));
        if (n < 0)
            break;
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}