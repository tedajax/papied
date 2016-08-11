#pragma once

#include "types.h"
#include "array.h"

class PaletteLibrary {
public:
    PaletteLibrary(foundation::Allocator& allocator);
    ~PaletteLibrary();

    void add_palette();
    void remove_palette(int paletteIndex);

    void add_color(int paletteIndex, Color color);
    void remove_color(int paletteIndex, int colorIndex);
    void change_color(int paletteIndex, int colorIndex, Color color);

    Texture get_texture(int paletteIndex);

private:
    void rebuild_texture(int paletteIndex);

private:
    foundation::Array<ColorPalette> m_palettes;
    foundation::Array<Texture> m_textures;
};