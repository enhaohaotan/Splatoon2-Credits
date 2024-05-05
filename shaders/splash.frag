#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float offsetY;
uniform vec3 splashColor;
uniform sampler2D splashSampler;
uniform sampler2D graffitiSampler;

void main() {
    vec4 texColor = texture(splashSampler, gl_PointCoord);
    vec2 grafCoord = vec2(0.5 * TexCoord.x + 0.25 + 0.5 * gl_PointCoord.s, 0.5 * TexCoord.y + 0.25 + 0.5 * gl_PointCoord.t + 0.9375 * offsetY);
    vec4 grafColor = texture(graffitiSampler, grafCoord);
//    vec4 grafColor = texture(graffitiSampler, gl_PointCoord - TexCoord);
    FragColor = vec4(splashColor.r * grafColor.r,  splashColor.g * grafColor.g, splashColor.b * grafColor.b, texColor.a < 1.0 ? 0.0 : 1.0);
}
