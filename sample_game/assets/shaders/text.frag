#version 400

in vec2 vs_uv;

out vec4 fragColor;

uniform sampler2D u_tex;
uniform vec4 u_color;

void main() {
    vec4 texColor = texture(u_tex, vs_uv).rgba;
    fragColor = u_color;
    fragColor.a = texColor.r;
}