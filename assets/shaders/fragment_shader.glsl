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
} light;

uniform sampler2D materialTex;
uniform mat4 Model;

void main() 
{
  float materialShininess     = 80.0f;
  vec3 materialSpecularColor  = vec3( 1.0, 1.0, 1.0 );
  vec3 cameraPosition = vec3( 2.0, 3.0, -5.0 );

  vec3 normal = normalize(transpose(inverse(mat3(Model))) * fragNormal);
  vec3 surfacePos = vec3(Model * vec4(fragVert, 1));
  vec4 surfaceColor = texture(materialTex, fragTexCoord);
  vec3 surfaceToLight = normalize(light.position - surfacePos);
  vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
    
  //ambient
  vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

  //diffuse
  float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
  vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
  //specular
  float specularCoefficient = 0.0;
  if(diffuseCoefficient > 0.0)
      specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
  vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;
    
  //attenuation
  float distanceToLight = length(light.position - surfacePos);
  float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

  //linear color (color before gamma correction)
  vec3 linearColor = ambient + attenuation*(diffuse + specular);
    
  //final color (after gamma correction)
  vec3 gamma = vec3(1.0/2.2);
  finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);
}
