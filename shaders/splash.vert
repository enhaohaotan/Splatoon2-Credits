#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aSize;

out vec2 TexCoord;

uniform float offsetY;

void main() {
    gl_Position = vec4(aPos, 1.0);
    gl_PointSize = aSize;
    TexCoord = vec2(aPos.x, 1 - aPos.y);
//    TexCoord = vec2(aPos.x, aPos.y);
}