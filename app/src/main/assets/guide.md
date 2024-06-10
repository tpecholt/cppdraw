# Programmer's Guide

Welcome to [CppDraw](https://github.com/tpecholt/cppdraw)!

CppDraw uses [SFML](https://www.sfml-dev.org/documentation) library under the hood and you get full access to it by including appropriate SFML headers.

For begginer-friendly API start by #including *cppdraw.h* documented below.

User code must contain *void draw(float time)* function which will be called upon rendering.

## API Reference

void *bkcolor*(sf::Color c);

void *circle*(float x, float y, float radius);

void *color*(sf::Color c);

void *convexPoly*(std::span<Sf::Vector2d> coords);

float *maxX*();

float *maxY*();

void *line*(float x1, float y1, float x2, float y2);

void *rectangle*(float x, float y, float w, float h);

void *text*(float x, float y, std::string_view str);

auto *textExtents*(std::string_view str) -> Sf::Vector2f;

void *textStyle*(std::string_view fontName, float size);

void *thickness*(float th);

