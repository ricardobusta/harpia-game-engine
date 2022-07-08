#version 400

in VS_OUT
{
   vec3 normal;
   vec2 uv;
} vs_in;

out vec4 fragColor;

uniform sampler2D u_tex;
uniform vec4 u_color;

void main() {
   fragColor.a = u_color.a;
   fragColor.rg = vs_in.uv;
   fragColor.rgb = vs_in.normal.xyz;
   fragColor.rgba = texture( u_tex, vs_in.uv ).rgba;
}