#version 150 core

in vec3 vPosition;
in vec3 vUV;
in vec3 vNormal;
out vec3 color;
out vec2 Texcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

void main() 
{
  vec3 Ld = vec3(1.0, 1.0, 1.0);
  vec3 Kd = vec3(1.0, 1.0, 1.0);
  vec4 LightPosition = View * vec4( 0.0, 2.0, 0.0, 1.0 );
  vec3 tnorm        = normalize( vec3 ( Model * vec4( vNormal, 1.0 ) ) );
  vec4 eyeCoords    = View * Model * vec4( vPosition, 1.0 );
  vec3 s = normalize( vec3( LightPosition - eyeCoords ) );
  // The diffuse shading equation
  color = 0.2 * Ld + Ld * Kd * max( dot( s, tnorm ), 0.0 );
  // Convert position to clip coordinates and pass along
  Texcoord = vec2( vUV.x, vUV.y);
  gl_Position = Proj * View * Model * vec4(vPosition,1.0);
}
