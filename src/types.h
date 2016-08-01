#pragma once

#include "debug.h"
#include "basic_types.h"
#include "collection_types.h"
#include "memory_types.h"

struct Color
{
    uint8 a = 255, r = 255, g = 255, b = 255;
};

struct SDL_Texture;
struct Texture
{
    SDL_Texture* _sdlTexture = nullptr;
    int width;
    int height;
};

