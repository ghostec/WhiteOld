#version 150 core

in vec3 vPosition;
in vec3 vUV;
in vec3 vNormal;

uniform mat4 Model;

uniform struct Camera
{
  mat4 view;
  mat4 proj;
} camera;

void main() 
{
  // Pass some variables to the fragment shader
  gl_Position = Model * vec4(vPosition,1.0);
}
