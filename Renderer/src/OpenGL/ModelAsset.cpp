#include "Renderer/OpenGL/ModelAsset.h"

ModelAsset::ModelAsset( std::string file_path, ModelAssetType type )
{
  this->model_asset_type = type;

  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  std::vector< WMath::vec3 > vertices;
  std::vector< WMath::vec3 > uvs;
  std::vector< WMath::vec3 > normals;
  std::vector< std::array<GLushort, 3> > elements;

  file_path = "../assets/models/" + file_path;
  ModelAssetHelper::ImportOBJ( file_path.c_str(), vertices, uvs, normals, elements );

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < elements.size(); i++ )
  {
    new_vertices.push_back( vertices.at( elements.at( i )[0] ) );
    new_vertices.push_back( uvs.at( elements.at( i )[1] ) );
    new_vertices.push_back( normals.at( elements.at( i )[2] ) );
  }

  this->vertices_count = elements.size();

  glBufferData( GL_ARRAY_BUFFER, elements.size() * ( 3 * sizeof( WMath::vec3 ) ),
                &new_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

ModelAsset::ModelAsset( ModelAssetData data, ModelAssetType type )
{
  this->model_asset_type = model_asset_type;

  // Create Vertex Array Object
  glGenVertexArrays( 1, &this->vao );
  glBindVertexArray( vao );

  // Create a Vertex Buffer Object
  glGenBuffers( 1, &this->vbo );
  glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < data.elements.size(); i++ )
  {
    new_vertices.push_back( data.vertices.at( data.elements.at( i )[0] ) );
    new_vertices.push_back( data.uvs.at( data.elements.at( i )[1] ) );
    new_vertices.push_back( data.normals.at( data.elements.at( i )[2] ) );
  }

  this->vertices_count = data.elements.size( );

  glBufferData( GL_ARRAY_BUFFER, data.elements.size( ) * ( 3 * sizeof( WMath::vec3 ) ),
                &new_vertices[0], GL_STATIC_DRAW );

  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glBindVertexArray( 0 );
}

void ModelAsset::configureShader( std::shared_ptr<Shader> shader )
{
  glBindVertexArray( this->vao );
  glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

  shader->setVertexAttribute( "vPosition", 3, 3 * sizeof( WMath::vec3 ),
    0 );
  shader->setVertexAttribute( "vUV", 3, 3 * sizeof( WMath::vec3 ),
    sizeof( WMath::vec3 ) );
  shader->setVertexAttribute( "vNormal", 3, 3 * sizeof( WMath::vec3 ),
    2 * sizeof( WMath::vec3 ) );

  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glBindVertexArray( 0 );
}

void ModelAsset::setTexture( std::shared_ptr<Texture> texture )
{
  this->texture = texture;
}

void ModelAsset::before_draw( std::shared_ptr<Shader> shader )
{
  glBindVertexArray( this->vao );
  if( this->model_asset_type == MODEL_ASSET_2D )
  {
    glDisable( GL_DEPTH_TEST );
  }
  else
  {
    glEnable( GL_DEPTH_TEST );
  }
  this->texture->use( shader );
}

void ModelAsset::after_draw()
{
  this->texture->unuse();
  glBindVertexArray(0);
}

void ModelAsset::draw
( std::shared_ptr<Shader> shader )
{
  this->before_draw( shader );
  shader->use( );
  if( shader->getDrawMode( ) == DM_NORMAL )
    glDrawArrays( GL_TRIANGLES, 0, this->vertices_count );
  else if( shader->getDrawMode( ) == DM_WIRE )
    glDrawArrays( GL_LINE_STRIP, 0, this->vertices_count );
  shader->unuse( );
  this->after_draw();
}