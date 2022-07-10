#version 400
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUv;

uniform mat4 harpia_WorldToObject;
uniform mat4 harpia_ObjectToCamera;

out VS_OUT
{
   vec3 normal;
   vec2 uv;
} vs_out;

void main() {
   gl_Position = harpia_ObjectToCamera * harpia_WorldToObject * vec4( inPos, 1.0 );
   vs_out.normal = normalize(inNormal);
   vs_out.uv = inUv;
}