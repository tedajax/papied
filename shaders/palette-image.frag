#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D indexTexture;
uniform sampler2D paletteTexture;

void main() {
    float findex = texture(indexTexture, uv).r;
    // highp int index = int(findex * 255);
    vec3 diffuse = texture(paletteTexture, vec2(findex, 0)).rgb;
    //gl_FragColor = vec4(diffuse, 1.0);
    color = vec4(diffuse, 1.0);
}