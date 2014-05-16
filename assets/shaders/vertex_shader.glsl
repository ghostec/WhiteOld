#version 150 core
in vec3 position;
in vec3 normal;
out vec4 color;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 proj;

const vec3 vEyeSpaceCameraPosition = vec3(0,0,0);

void main() 
{
  vec4 nPosition              = view * transformation * vec4( position, 1.0 );
  vec3 light_position         = vec3(0.0, 100000.0, -100000.0);
  vec3 diffuse_color          = vec3( 1.0, 1.0, 1.0 );
  vec3 specular_color         = vec3( 1.0, 1.0, 1.0 );
  float shininess             = 0.2;
  mat3 inverseTranspose       = transpose( inverse( mat3( view * transformation ) ) );
  vec4 vEyeSpaceLightPosition = view * transformation * vec4( light_position, 1 );
  vec4 vEyeSpacePosition      = view * transformation * nPosition;
  vec3 vEyeSpaceNormal        = normalize( inverseTranspose * normal );
  vec3 L                      = normalize( vEyeSpaceLightPosition.xyz - vEyeSpacePosition.xyz );
  vec3 V = normalize( vEyeSpaceCameraPosition.xyz - vEyeSpacePosition.xyz );
  vec3 H = normalize( L + V );
  float diffuse  = max(0, dot(vEyeSpaceNormal, L));
  float specular = max( 0, pow(dot(vEyeSpaceNormal, H), shininess) );
  color = 0.0 * vec4( diffuse_color, 1.0 ) +
          diffuse * vec4( diffuse_color, 1.0 ) +
          specular * vec4( specular_color, 1.0 );
  gl_Position = proj * nPosition;
}
