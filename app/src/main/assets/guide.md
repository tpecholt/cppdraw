# Programmer's Guide

Welcome to [CppDraw](https://github.com/tpecholt/cppdraw)! CppDraw provides an easy platform to test your C++ skills in a visual way.

Start by #including *cppdraw.h* documented below.

User code must contain *void draw(float time)* function which will be called upon rendering.

## API Reference

### Types

using *clr* = unsigned;

clr *RGB*(char r, char g, char b, char a = 255);

struct *vec2* { 
   float x, y; 
};

### Functions - Rendering

void *bkcolor*(clr c);

void *circle*(float x, float y, float radius);

void *color*(clr c);

void *convexPoly*(std::span<vec2> coords);

float *maxX*();

float *maxY*();

void *line*(float x1, float y1, float x2, float y2);

void *rectangle*(float x, float y, float w, float h);

void *text*(float x, float y, std::string_view str);

vec2 *textExtents*(std::string_view str);

void *textStyle*(std::string_view fontName, float size);

void *thickness*(float thick);

### Functions - Interactions

bool *isTouchDown*();

vec2 *touchPos*();

.