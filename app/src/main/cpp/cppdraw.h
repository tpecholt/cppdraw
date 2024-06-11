#pragma once
#include <vector>

using clr = unsigned;
struct vec2 { float x, y; };

clr color_;
float thickness_;
bool touchDown_;
vec2 touchPos_;
float maxX_, maxY_;
struct Shape {
    enum Kind { Line, Rect };
    Kind kind;
    float x1, y1, x2, y2, r;
    clr fg, bg;
    float thick;
    Shape(Kind k)
        : kind(k), fg(color_), bg(), thick(thickness_)
    {}
};
static std::vector<Shape> shapes_; //todo: move to cpp

inline clr RGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255)
{
    return (a << 24) | (b << 16) | (g << 8) | r;
}

inline void color(clr c)
{
    color_ = c;
}

inline void line(float x1, float y1, float x2, float y2)
{
    Shape line(Shape::Line);
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    shapes_.push_back(line);
}

extern "C" void draw(float time);

inline void shapes_clear_()
{
    shapes_.clear();
}

inline size_t get_shapes_(const Shape** out)
{
    *out = shapes_.data();
    return shapes_.size();
}

