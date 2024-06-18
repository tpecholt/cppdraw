#pragma once

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

struct Shape {
    enum Kind { Line, Rect };
    Kind kind;
    float x1, y1, x2, y2, r;
    clr fg, bg;
    float thick;
    Shape(Kind k);
};

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

void color(clr c);

void line(float x1, float y1, float x2, float y2);

extern void draw(float time);
