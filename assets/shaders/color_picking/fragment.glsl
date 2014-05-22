#version 150 core

uniform vec3 unique_id;

out vec4 finalColor;

void main() 
{
  finalColor = vec4( unique_id, 1.0 );
}
