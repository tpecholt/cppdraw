# Programmer's Guide

Welcome to [CppDraw](https://github.com/tpecholt/cppdraw)! CppDraw provides an easy platform to test your C++ skills in a visual way.

Start by #including *cppdraw.h* documented below.

User code must contain *void draw()* function which will be called upon rendering.

## API Reference

### Types

using *clr* = unsigned;

clr *RGB*(char r, char g, char b, char a = 255);

struct *vec2* { 
   float x, y; 
};

### Functions - Rendering

void *circle*(float x, float y, float radius);

void *color*(clr c);

void *convexPoly*(const std::vector<vec2>& coords);

void *line*(float x1, float y1, float x2, float y2);

void *rectangle*(float x, float y, float w, float h);

void *fillRect*(float x, float y, float w, float h);

vec2 *screenSize*();

void *text*(float x, float y, StringView str);

vec2 *textExtents*(StringView str);

void *textStyle*(StringView fontName, float size);

void *thickness*(float thick);

### Functions - User Interaction

float *time*();

bool *touchDown*();

vec2 *touchPos*();
