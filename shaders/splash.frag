#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 splashColor;
uniform sampler2D splashSampler;
uniform sampler2D graffitiSampler;

void main() {
    vec4 texColor = texture(splashSampler, gl_PointCoord);
    vec2 grafCoord = vec2(TexCoord.x - 0.25 + 0.5 * gl_PointCoord.x, TexCoord.y - 0.25 + 0.5 * gl_PointCoord.y);
    vec4 grafColor = texture(graffitiSampler, grafCoord);
    FragColor = vec4(splashColor.r * grafColor.r,  splashColor.g * grafColor.g, splashColor.b * grafColor.b, texColor.a < 1.0 ? 0.0 : 1.0);
}
