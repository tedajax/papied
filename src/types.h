#pragma once

#include "debug.h"
#include "basic_types.h"
#include "collection_types.h"
#include "memory_types.h"

struct Color
{
    uint8 a = 255, r = 255, g = 255, b = 255;
};

static const int cPaletteMaxColors = 32;
struct ColorPalette {
    Color colors[cPaletteMaxColors];
    int size = 0;
};

struct PaletteImage {
    int _width = 0;
    int _height = 0;
    int _size = 0;
    uint8* _data = nullptr;
};

struct SDL_Texture;
struct Texture
{
    SDL_Texture* _sdlTexture = nullptr;
    int width;
    int height;
};

