#version 150 core

in vec3 vPosition;
in vec3 vUV;
in vec3 vNormal;
out vec2 fragTexCoord;
out vec3 fragVert;
out vec3 fragNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

void main() 
{
  // Pass some variables to the fragment shader
  fragTexCoord = vec2( vUV.x, vUV.y );
  fragNormal = vNormal;
  fragVert = vPosition; 
  gl_Position = Proj * View * Model * vec4(vPosition,1.0);
}
