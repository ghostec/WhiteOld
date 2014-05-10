#version 150 core
in vec3 position;

uniform _SceneProperties
{
  mat4 view;
  mat4 proj;
} SceneProperties;

uniform mat4 transformation;

void main() {
  gl_Position = SceneProperties.proj *
                SceneProperties.view * 
                transformation * vec4(position, 1.0);
}
