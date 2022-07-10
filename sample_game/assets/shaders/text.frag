#version 400

in vec3 vs_normal;
in vec2 vs_uv;

out vec4 fragColor;

uniform sampler2D u_tex;
uniform vec4 u_color;

void main() {
    fragColor.a = u_color.a;
    fragColor.rg = vs_uv;
    fragColor.rgb = vs_normal.xyz;
    fragColor.rgba = texture(u_tex, vs_uv).rgba;
}