#pragma once
//#include <string_view> //todo: provide lightweight version to speed up compile time
#include <stddef.h>
#include <cstring>
#include <cmath>

const int CPPDRAW_PORT = 5551;

struct ZStringView {
    ZStringView()
        : str_(), size_()
    {}
    ZStringView(const char* s)
        : str_(s), size_(std::strlen(s))
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

    vec2() : x(), y() {}
    vec2(float x, float y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}
    vec2 operator+ (vec2 v) const { return { x+v.x, y+v.y }; }
    vec2 operator- (vec2 v) const { return { x-v.x, y-v.y }; }
    vec2 operator* (float f) const { return { f*x, f*y }; }
    friend vec2 operator* (float f, vec2 v) { return v*f; }
    vec2 operator/ (float f) const { return { x/f, y/f }; }
    vec2& operator+= (vec2 v) { *this = *this + v; return *this; }
    vec2& operator-= (vec2 v) { *this = *this - v; return *this; }
    vec2& operator*= (float f) { *this = *this * f; return *this; }
    vec2& operator/= (float f) { *this = *this / f; return *this; }
    friend float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }
    friend float norm(vec2 a) { return std::sqrt(dot(a, a)); }
    friend float cross(vec2 a, vec2 b) { return a.x*b.y - a.y*b.x; }
};

struct DateTime {
    int h, m, s;
    int day, month, year;
};

struct DrawCmd {
    vec2 screenSize;
    int mouseDown;
    vec2 mousePos;
    vec2 mouseDelta;
    float time;
    float timeDelta;
    DateTime dateTime;
    bool keys[64];
};

struct LineShape {
    float x1, y1, x2, y2;
    clr color;
    float thick;
};
struct RectShape {
    float x1, y1, x2, y2;
    clr color;
    float thick;
};
struct CircleShape {
    float x1, y1, r;
    clr color;
    float thick;
};
struct TriangleShape {
    float x1, y1, x2, y2, x3, y3;
    clr color;
};
struct TextShape {
    float x1, y1;
    size_t text;
    size_t font;
    float size;
    clr color;
};

struct Shape {
    enum Kind { Line, Rect, FillRect, FillTriangle, Circle, FillCircle, Text };
    Kind kind;
    union {
        LineShape l;
        RectShape r;
        CircleShape c;
        TriangleShape t;
        TextShape x;
    };
    Shape(Kind k);
};

clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

//rendering

void color(clr c);

void font(ZStringView name, float fontSize);

void thickness(float th);

void line(float x1, float y1, float x2, float y2);

void rectangle(float x1, float y1, float x2, float y2);

void circle(float x1, float y1, float r);

void text(float x, float y, ZStringView text);

void fillRect(float x1, float y1, float x2, float y2);

void fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

void fillQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void fillCircle(float x1, float y1, float r);

vec2 screenSize();

//user interaction

float time();

float timeDelta();

DateTime dateTime();

bool mouseDown(int button = 0);

vec2 mousePos();

vec2 mouseDelta();

bool keyDown(int key);

//

void newFrame();

extern void draw();
