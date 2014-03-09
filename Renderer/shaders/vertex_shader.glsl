#version 150 core
in vec3 position;
out vec3 color;
uniform mat4 t;
uniform mat4 view;
uniform mat4 proj;
void main() {
  color = position;
  gl_Position = proj * view * t * vec4(position, 1.0);
}
