#version 400
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

uniform mat4 harpia_WorldToObject;
uniform mat4 harpia_ObjectToCamera;

out vec2 vs_uv;

void main() {
    gl_Position = harpia_ObjectToCamera * harpia_WorldToObject * vec4(in_position, 1.0);
    vs_uv = in_uv;
}