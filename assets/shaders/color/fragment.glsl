#version 150 core
in vec2 fragTexCoord;
in vec3 fragVert;
in vec3 fragNormal;
out vec4 finalColor;

uniform struct Light 
{
   vec3 position;
   vec3 intensities;
   float attenuation;
   float ambientCoefficient;
} lights[10];

uniform sampler2D materialTex;
uniform mat4 Model;
uniform vec3 color;

void main() 
{
  finalColor = vec4(color, 1.0);
}
