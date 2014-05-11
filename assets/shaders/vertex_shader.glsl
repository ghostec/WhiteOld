#version 150 core
in vec3 position;
out float distance;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 proj;

float distance2( vec3 p1, vec3 p2 )
{
  return (  pow(p1.x - p2.x, 2.0) + 
            pow(p1.y - p2.y, 2.0) + 
            pow(p1.z - p2.z, 2.0) );
}

void main() {
  vec3 light_position = vec3(0.0, 1.5, 0.5);
  distance = distance2( position, light_position );
  gl_Position = proj *
                view * 
                transformation * vec4(position, 1.0);
}
