#include "texture.h"
#include <GL/gl3w.h>

namespace texture {
    Texture create() {
        Texture result;
        glGenTextures(1, &result);
        return result;
    }

    void make_palette(Texture texture, const ColorPalette& palette) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, palette.size, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, palette.colors);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void make_index_image(Texture texture, const PaletteImage& image) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, image._width, image._height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, image._data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}