#pragma once
//#include <string_view> //todo: provide lightweight version to speed up compile time
#include <stddef.h>
#include <string.h>

const int CPPDRAW_PORT = 5551;

struct ZStringView {
    ZStringView()
        : str_(), size_()
    {}
    ZStringView(const char* s)
        : str_(s), size_(strlen(s))
    {}
    template <class T>
    ZStringView(const T& s)
        : str_(s.c_str()), size_(s.size())
    {}
    size_t size() const { return size_; }
    const char* c_str() const { return str_; }
    const char* begin() const { return c_str(); }
    const char* end() const { return begin() + size();}

private:
    const char* str_;
    size_t size_;
};

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
    clr color;
    float thick;
};
struct RectShape {
    float x1, y1, w, h;
    clr color;
    float thick;
};
struct CircleShape {
    float x1, y1, r;
    clr color;
    float thick;
};
struct TextShape {
    float x1, y1;
    size_t text;
    size_t font;
    float size;
    clr color;
};

struct Shape {
    enum Kind { Line, Rect, FillRect, Circle, Text };
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

void thickness(float th);

void line(float x1, float y1, float x2, float y2);

void rectangle(float x1, float y1, float w, float h);

void fillRect(float x1, float y1, float w, float h);

void circle(float x1, float y1, float r);

void text(float x, float y, ZStringView text);

vec2 screenSize();

//user interaction

float time();

bool touchDown();

vec2 touchPos();

//

extern void draw();
