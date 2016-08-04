#version 330 core

in vec2 uv;

uniform sampler2D indexTexture;
uniform sampler2D paletteTexture;

void main() {
    vec4 color = texture(indexTexture, uv);
    vec2 index = vec2(color.r, 0);
    vec3 diffuse = texture(paletteTexture, index).rgb;
    gl_FragColor = vec4(diffuse, 1.0);
}