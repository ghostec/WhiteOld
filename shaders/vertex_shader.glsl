#version 150 core
in vec2 position;
uniform mat4 t;
void main() {
  gl_Position = t * vec4(position, 0.0, 1.0);
}
