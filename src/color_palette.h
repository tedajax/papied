#pragma once

#include "types.h"

struct SDL_Surface;
namespace color_palette {
    void set_surface_palette(const ColorPalette& palette, SDL_Surface* surface);
}