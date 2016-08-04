#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vertUv;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    uv = vertUv;
    gl_Position = projection * view * model * vec4(position, 1.0);
}