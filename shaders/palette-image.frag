#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D indexTexture;
uniform sampler2D paletteTexture;

void main() {
    vec4 indexColor = texture(indexTexture, uv);
    float delta = 255.0 / textureSize(paletteTexture, 0).x;
    vec2 index = vec2(indexColor.r*delta, 0);
    vec3 diffuse = texture(paletteTexture, index).rgb;
    color = vec4(diffuse, 1.0);
}