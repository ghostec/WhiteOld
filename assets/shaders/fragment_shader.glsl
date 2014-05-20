#version 150 core
in vec3 color;
in vec2 Texcoord;
out vec4 outColor;

uniform sampler2D tex;

void main() {
  outColor = texture( tex, Texcoord );
}
