#version 400
layout (location = 0) in vec3 inPos;

uniform mat4 harpia_WorldToObject;
uniform mat4 harpia_ObjectToCamera;

void main() {
   gl_Position = harpia_ObjectToCamera * harpia_WorldToObject * vec4( inPos, 1.0 );
}