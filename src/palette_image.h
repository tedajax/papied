#pragma once

#include "types.h"

struct SDL_Surface;

namespace palette_image {
    PaletteImage create(int width, int height);
    void free(PaletteImage& image);
    void set_color(PaletteImage& image, int x, int y, int color);
    void create_surface(const PaletteImage& image, SDL_Surface** surface);
}