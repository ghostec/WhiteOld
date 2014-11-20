#include "Renderer/Heightmap.h"

Heightmap::Heightmap( std::string file_path )
{
  unsigned char* image;
  int width, height;
  image =
    SOIL_load_image( file_path.c_str(), &width, &height, 0, SOIL_LOAD_L );

  std::vector< WMath::vec3 > vertices, uvs;
  vertices.reserve( width * height ); uvs.reserve( width * height );

  float fTextureU = float( width ) * 0.1f;
  float fTextureV = float( height ) * 0.1f;

  for( int i = 0; i < height; i++ )
  {
    for( int j = 0; j < width; j++ )
    {
      float fScaleW = float( j ) / float( width - 1 );
      float fScaleH = float( i ) / float( height - 1 );
      float fVertexHeight = float( *( image + height * i + j ) ) / 255.0f;
      vertices.push_back
        ( WMath::vec3( -0.5f + fScaleW, fVertexHeight, -0.5f + fScaleH ) );
      uvs.push_back
        ( WMath::vec3( fTextureU*fScaleW, fTextureV*fScaleH, 0.0f ) );
    }
  }

  std::vector< WMath::vec3 > normals[2];
  normals[0].reserve( ( width - 1 ) * ( height - 1 ) );
  normals[1].reserve( ( width - 1 ) * ( height - 1 ) );

  for( int i = 0; i < height - 1; i++ )
  {
    for( int j = 0; j < width - 1; j++ )
    {
      WMath::vec3 vTriangle0[ ] =
      {
        vertices[ height * i + j ],
        vertices[ height * ( i + 1 ) + j ],
        vertices[ height * ( i + 1 ) + j + 1 ]
      };
      WMath::vec3 vTriangle1[ ] =
      {
        vertices[ height * ( i + 1 ) + j + 1 ],
        vertices[ height * i + j + 1 ],
        vertices[ height * i + j ]
      };

      WMath::vec3 vTriangleNorm0 =
        WMath::cross( vTriangle0[ 0 ] - vTriangle0[ 1 ],
        vTriangle0[ 1 ] - vTriangle0[ 2 ] );
      WMath::vec3 vTriangleNorm1 =
        WMath::cross( vTriangle1[ 0 ] - vTriangle1[ 1 ],
        vTriangle1[ 1 ] - vTriangle1[ 2 ] );

      normals[ 0 ].push_back( WMath::normalize( vTriangleNorm0 ) );
      normals[ 1 ].push_back( WMath::normalize( vTriangleNorm1 ) );
    }
  }
  
  std::vector< WMath::vec3 > final_normals;
  final_normals.reserve( width * height );

  for( int i = 0; i < height; i++ )
  {
    for( int j = 0; j < width; j++ )
    {
      WMath::vec3 vFinalNormal = WMath::vec3( 0.0f, 0.0f, 0.0f );

      // Look for upper-left triangles
      if( j != 0 && i != 0 )
        for( int k = 0; k < 2; k++ ) vFinalNormal += normals[ k ][ ( height - 1 ) * ( i - 1 ) + j - 1 ];
      // Look for upper-right triangles
      if( i != 0 && j != width - 1 ) vFinalNormal += normals[ 0 ][ ( height - 1 ) * ( i - 1 ) + j ];
      // Look for bottom-right triangles
      if( i != height - 1 && j != width - 1 )
        for( int k = 0; k < 2; k++ ) vFinalNormal += normals[ k ][ ( height - 1 ) * i + j ];
      // Look for bottom-left triangles
      if( i != height - 1 && j != 0 )
        vFinalNormal += normals[ 1 ][ ( height - 1 ) * i + j - 1 ];
      vFinalNormal = WMath::normalize( vFinalNormal );

      final_normals.push_back( vFinalNormal ); // Store final normal of j-th vertex in i-th row
    }
  }

  std::vector< int > indices;
  int iPrimitiveRestartIndex = width * height;

  for( int i = 0; i < height - 1; i++ )
  {
    for( int j = 0; j < width; j++ )
    {
      for( int k = 0; k < 2; k++ )
      {
        int iRow = i + ( 1 - k );
        int iIndex = iRow * width + j;
        indices.push_back( iIndex );
      }
    }
    indices.push_back( iPrimitiveRestartIndex );
  }

  this->mesh.reset( new Mesh( MESH_V3NT, MESH_INDEXED ) ); // TODO INDEXED ON Mesh::resetVBO

  mesh->setVertices( vertices );
  mesh->setUVs( uvs );
  mesh->setNormals( final_normals );
  mesh->setIndices( indices );
  mesh->resetVBO();
}