#include "Renderer/OpenGL/GUI.h"

GUI::GUI( float offset_x, float offset_y, float ar, float percent )
{
  float parent_width = 800;
  float parent_height = 600;

  float width, height;
  if( parent_width < parent_height )
  {
    width = percent * parent_width;
    height = width / ar;
  }
  else
  {
    height = percent * parent_height;
    width = height * ar;
  }

  vertices.push_back( WMath::vec3(  2.0f * offset_x / parent_width - 1.0f, 
                                    2.0f * offset_y / parent_height - 1.0f, 
                                    0.0f ) );
  vertices.push_back( WMath::vec3(  2.0f * ( offset_x + width ) / parent_width - 1.0f,
                                    2.0f * offset_y / parent_height - 1.0f,
                                    0.0f ) );
  vertices.push_back( WMath::vec3(  2.0f * offset_x / parent_width - 1.0f,
                                    2.0f * ( offset_y + height ) / parent_height - 1.0f,
                                    0.0f ) );
  vertices.push_back( WMath::vec3(  2.0f * ( offset_x + width ) / parent_width - 1.0f,
                                    2.0f * ( offset_y + height ) / parent_height - 1.0f,
                                    0.0f ) );
  
  uvs.push_back( WMath::vec3( 0.0f, 0.0f, 0.0f ) );
  uvs.push_back( WMath::vec3( 1.0f, 0.0f, 0.0f ) );
  uvs.push_back( WMath::vec3( 0.0f, 1.0f, 0.0f ) );
  uvs.push_back( WMath::vec3( 1.0f, 1.0f, 0.0f ) );

  normals.push_back( WMath::vec3( 0.0f, 0.0f, 1.0f ) );
  normals.push_back( WMath::vec3( 0.0f, 0.0f, 1.0f ) );
  normals.push_back( WMath::vec3( 0.0f, 0.0f, 1.0f ) );
  normals.push_back( WMath::vec3( 0.0f, 0.0f, 1.0f ) );

  std::array<GLushort, 3> elem1 = { 0, 0, 0 };
  elements.push_back( elem1 );
  std::array<GLushort, 3> elem2 = { 1, 1, 1 };
  elements.push_back( elem2 );
  std::array<GLushort, 3> elem3 = { 2, 2, 2 };
  elements.push_back( elem3 );
  std::array<GLushort, 3> elem4 = { 2, 2, 2 };
  elements.push_back( elem4 );
  std::array<GLushort, 3> elem5 = { 1, 1, 1 };
  elements.push_back( elem5 );
  std::array<GLushort, 3> elem6 = { 3, 3, 3 };
  elements.push_back( elem6 );
}