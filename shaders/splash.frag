#version 330 core
out vec4 FragColor;

uniform vec3 splashColor;
uniform sampler2D textureSampler;

void main() {

    vec4 texColor = texture(textureSampler, gl_PointCoord);
    FragColor = vec4(splashColor, texColor.a);
}
