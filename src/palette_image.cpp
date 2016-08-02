#include "palette_image.h"

namespace palette_image {
    PaletteImage create(int width, int height) {
        PaletteImage image;
        image._width = width;
        image._height = height;
        image._size = width * height;
        image._data = new uint8[image._size];
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
}