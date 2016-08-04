#include "palette_image.h"
#include "color_palette.h"
#include <SDL2/SDL.h>
#include <cstdio>

namespace palette_image {
    PaletteImage create(int width, int height, ColorPalette* palette) {
        PaletteImage image;
        image._width = width;
        image._height = height;
        image._size = width * height;
        image._data = new uint8[image._size];
        image.palette = palette;
        return image;
    }

    void free(PaletteImage& image) {
        if (image._data) {
            delete image._data;
        }
    }

    void set_color(PaletteImage& image, int x, int y, int color) {
        int index = y * image._width + x;
        image._data[index] = color;
    }

    void create_surface(const PaletteImage& image, SDL_Surface** surfacePtr) {
        if (*surfacePtr == nullptr) {
            *surfacePtr = SDL_CreateRGBSurface(0, image._width, image._height, 8, 0, 0, 0, 0);
        }

        SDL_Surface* surface = *surfacePtr;
        ASSERT(image._width == surface->w && image._height == surface->h, "Image/Surface size mismatch.");

        SDL_LockSurface(surface);

        uint8* pixelData = (uint8*)surface->pixels;
        for (int i = 0; i < image._size; ++i) {
            pixelData[i] = image._data[i];
        }

        SDL_UnlockSurface(surface);

        color_palette::set_surface_palette(*image.palette, surface);
    }
}