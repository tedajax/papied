#include "color_palette.h"
#include <SDL2/SDL.h>

namespace color_palette {
    void set_surface_palette(const ColorPalette& palette, SDL_Surface* surface) {
        SDL_Color sdlColors[cPaletteMaxColors] = { { 0, 0, 0, 0 } };
        for (int i = 0; i < palette.size; ++i) {
            sdlColors[i].r = palette.colors[i].r;
            sdlColors[i].g = palette.colors[i].g;
            sdlColors[i].b = palette.colors[i].b;
            sdlColors[i].a = palette.colors[i].a;
        }
        SDL_SetPaletteColors(surface->format->palette, sdlColors, 0, palette.size);
    }
}