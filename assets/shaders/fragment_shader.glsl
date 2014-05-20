#version 150 core
in vec2 fragTexCoord;
in vec3 fragVert;
in vec3 fragNormal;
out vec4 outColor;

uniform sampler2D tex;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

void main() 
{
  vec3 lightIntensities = vec3( 1.0, 1.0, 1.0);
  vec3 lightPosition = vec3(0.0, 0.0, -3.0);
  //calculate normal in world coordinates
  mat3 normalMatrix = transpose(inverse(mat3(Model)));
  vec3 normal = normalize(normalMatrix * fragNormal);
  //calculate the location of this fragment (pixel) in world coordinates
  vec3 fragPosition = vec3(Model * vec4(fragVert, 1));
  //calculate the vector from this pixels surface to the light source
  vec3 surfaceToLight = lightPosition - fragPosition;
  //calculate the cosine of the angle of incidence (brightness)
  float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
  brightness = clamp(brightness, 0, 1);
  outColor = brightness * vec4(lightIntensities, 1) * texture( tex, fragTexCoord );
}
