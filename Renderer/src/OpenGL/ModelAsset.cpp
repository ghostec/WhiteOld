#include "Renderer/OpenGL/ModelAsset.h"

ModelAsset::ModelAsset( std::string file_path, ModelAssetType model_asset_type )
{
  this->model_asset_type = model_asset_type;

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

ModelAsset::ModelAsset( std::vector< WMath::vec3 > vertices,
                        std::vector< WMath::vec3 > uvs,
                        std::vector< WMath::vec3 > normals,
                        std::vector< std::array<GLushort, 3> > elements,
                        ModelAssetType model_asset_type )
{
  this->model_asset_type = model_asset_type;

  // Create Vertex Array Object
  glGenVertexArrays( 1, &this->vao );
  glBindVertexArray( vao );

  // Create a Vertex Buffer Object
  glGenBuffers( 1, &this->vbo );
  glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < elements.size(); i++ )
  {
    new_vertices.push_back( vertices.at( elements.at( i )[0] ) );
    new_vertices.push_back( uvs.at( elements.at( i )[1] ) );
    new_vertices.push_back( normals.at( elements.at( i )[2] ) );
  }

  this->vertices_count = elements.size( );

  glBufferData( GL_ARRAY_BUFFER, elements.size( ) * ( 3 * sizeof( WMath::vec3 ) ),
                &new_vertices[0], GL_STATIC_DRAW );

  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glBindVertexArray( 0 );
}

void ModelAsset::addShader( Shader* shader )
{
  this->shaders.push_back( shader );
  this->configureShader( shader );
}

void ModelAsset::configureShader( Shader* shader )
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

void ModelAsset::setTexture( Texture* texture )
{
  this->texture = texture;
}

void ModelAsset::before_draw()
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
  this->texture->use( this->shaders[0] );
}

void ModelAsset::after_draw()
{
  this->texture->unuse();
  glBindVertexArray(0);
}

void ModelAsset::drawWithShaders( std::vector< Shader* >* shaders )
{
  for( Shader* shader : *shaders )
  {
    shader->use( );
    if( shader->getDrawMode( ) == DM_NORMAL )
      glDrawArrays( GL_TRIANGLES, 0, this->vertices_count );
    else if( shader->getDrawMode() == DM_WIRE )
      glDrawArrays( GL_LINE_STRIP, 0, this->vertices_count );
    shader->unuse( );
  }
}

void ModelAsset::draw( std::vector< Shader* >* instance_shaders )
{
  this->before_draw();
  this->drawWithShaders( &this->shaders );
  this->drawWithShaders( instance_shaders );
  this->after_draw();
}