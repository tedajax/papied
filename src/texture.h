#pragma once

#include "types.h"

struct SDL_Surface;

namespace texture {
    Texture create();
    void make_palette(Texture texture, const PaletteImage& image);
    void make_index_image(Texture texture, const PaletteImage& image);
}