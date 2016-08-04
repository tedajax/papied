#include <cstdio>
#include "texture.h"
#include <GL/gl3w.h>

namespace texture {
    Texture create() {
        Texture result;
        glGenTextures(1, &result);
        return result;
    }

    void make_palette(Texture texture, const PaletteImage& image) {
        ColorPalette palette = *image.palette;
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, palette.size, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, palette.colors);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void make_index_image(Texture texture, const PaletteImage& image) {
        uint8* data = new uint8[image._size];
        uint8 delta = 255 / image.palette->size;
        for (int i = 0; i < image._size; ++i) {
            data[i] = image._data[i] * delta;
        }

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, image._width, image._height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        delete[] data;
    }
}