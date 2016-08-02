#pragma once

#include "types.h"

namespace palette_image {
    PaletteImage create(int width, int height);
    void free(PaletteImage& image);
    void set_color(PaletteImage& image, int x, int y, int color);
}