#version 150 core
in float distance;
out vec4 outColor;
uniform vec3 color;

void main() {
  float k = 0.3;
  vec3 color_distance = color / distance;
  outColor = k*vec4(color, 1.0) + vec4(color_distance, 1.0);
}
