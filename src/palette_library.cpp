#include "palette_library.h"

using namespace foundation;

PaletteLibrary::PaletteLibrary(Allocator& allocator)
    : m_palettes(allocator),
    m_textures(allocator)
{
}

PaletteLibrary::~PaletteLibrary() {

}

void PaletteLibrary::add_palette() {
    array::push_back(m_palettes, ColorPalette());
    array::push_back(m_textures, 0xFFFFFFFF);
}

void PaletteLibrary::remove_palette(int paletteIndex) {
    
}

void PaletteLibrary::add_color(int paletteIndex, Color color) {

}

void PaletteLibrary::remove_color(int paletteIndex, int colorIndex) {

}

void PaletteLibrary::change_color(int paletteIndex, int colorIndex, Color color) {

}

Texture PaletteLibrary::get_texture(int paletteIndex) {

}

void PaletteLibrary::rebuild_texture(int paletteIndex) {

}