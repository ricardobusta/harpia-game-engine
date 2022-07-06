#version 400

out vec4 fragColor;

uniform vec4 u_color;

void main() {
   fragColor = u_color;
}