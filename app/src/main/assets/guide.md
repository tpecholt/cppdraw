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

struct *DateTime* {
   int h, m, s;
   int day, month, year; 
};

### Functions - Rendering

void *circle*(float x, float y, float radius);

void *color*(clr c);

void *fillCircle*(float x, float y, float radius);

void *fillQuad*(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void *fillRect*(float x, float y, float w, float h);

void *fillTriangle*(float x1, float y1, float x2, float y2, float x3, float y3);

void *font*(StringView fontName, float fontSize);

void *line*(float x1, float y1, float x2, float y2);

void *rectangle*(float x, float y, float w, float h);

vec2 *screenSize*();

void *text*(float x, float y, StringView str);

void *thickness*(float thick);

### Functions - User Interaction

float *time*();

float *timeDelta*();

DateTime *dateTime*();

bool *mouseDown*();

vec2 *mousePos*();

vc2 *mouseDelta*();

bool *keyDown*(int);