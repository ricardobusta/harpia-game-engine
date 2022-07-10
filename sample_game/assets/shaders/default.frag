#version 400

in vec3 vs_normal;
in vec2 vs_uv;

out vec4 fragColor;

uniform sampler2D u_tex;
uniform vec4 u_color;

void main() {
    vec4 textureColor = texture(u_tex, vs_uv).rgba;
    float normalColor = max(0.5f, dot(vs_normal, vec3(0, 0, - 1)));
    fragColor.rgb = textureColor.rgb * u_color.rgb * normalColor;
    fragColor.a = textureColor.a;
}