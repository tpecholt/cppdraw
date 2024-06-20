#pragma once
#include <string_view> //todo: provide own version to speed up compile time

const int CPPDRAW_PORT = 5551;

using clr = unsigned;

struct vec2 {
    float x, y;
};

struct DrawCmd {
    vec2 screenSize;
    int touchDown;
    vec2 touchPos;
    float time;
};

struct LineShape {
    float x1, y1, x2, y2;
    clr fg;
    float thick;
};
struct RectShape {
    float x1, y1, w, h;
    clr fg, bg;
    float thick;
};
struct CircleShape {
    float x1, y1, r;
    clr fg, bg;
    float thick;
};
struct TextShape {
    float x1, y1;
    const char* text;
    const char* font;
    float size;
    clr fg;
};

struct Shape {
    enum Kind { Line, Rect, Circle, Text };
    Kind kind;
    union {
        LineShape l;
        RectShape r;
        CircleShape c;
        TextShape t;
    };
    Shape(Kind k);
};

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

//rendering

void color(clr c);

void bkcolor(clr c);

void thickness(float th);

void line(float x1, float y1, float x2, float y2);

void rectangle(float x1, float y1, float w, float h);

void circle(float x1, float y1, float r);

void text(float x, float y, std::string_view text);

//user interaction

float time();

bool touchDown();

vec2 touchPos();

//

extern void draw();
