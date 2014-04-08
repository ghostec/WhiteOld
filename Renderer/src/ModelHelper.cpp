#include "Renderer/ModelHelper.h"

namespace ModelHelper
{
  void ImportOBJ(
      std::string filePath,
      std::vector< WMath::vec3 >* vertices,
      std::vector< WMath::vec3 >* normals,
      std::vector< GLuint >* vertexIndices,
      std::vector< GLuint >* normalIndices,
      std::vector< GLuint >* uvIndices
      )
  {
    FILE* file = std::fopen(filePath.c_str(), "r");
    std::vector< WMath::vec3 > tmp_normals;
    if( file == NULL )
    {
      printf("Impossible to open the file !\n");
      return;
    }
    char lineHeader[512];
    int res = fscanf(file, "%s", lineHeader);
    float max = 0.0f, max_tmp;
    float sum[] = { 0.0f, 0.0f, 0.0f };
    while( res != EOF ){
      // Vertex
      if ( strcmp( lineHeader, "v" ) == 0 )
      {
        WMath::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2] );
        vertices->push_back(vertex);
        if( vertex[0] > vertex[1] )
          max_tmp = vertex[0];
        else
          max_tmp = vertex[1];
        if( vertex[2] > max_tmp )
          max_tmp = vertex[2];
        if( max_tmp > max )
          max = max_tmp;
        //sum[0] += vertex[0]; sum[1] += vertex[1]; sum[2] += vertex[2];
      }
      // Face
      else if ( strcmp( lineHeader, "f" ) == 0 )
      {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d %d %d\n",
            &vertexIndex[0],
            &vertexIndex[1],
            &vertexIndex[2] );
        if (matches != 3)
        {
          printf("File can't be read by our simple parser :( ");
          printf("Try exporting with other options\n");
          return;
        }
        vertexIndices->push_back(vertexIndex[0] - 1);
        vertexIndices->push_back(vertexIndex[1] - 1);
        vertexIndices->push_back(vertexIndex[2] - 1);
      }
      res = fscanf(file, "%s", lineHeader);
    }
    for( int i=0 ; i < vertices->size(); i++ )
    {
      vertices->at(i)[0] = vertices->at(i)[0] / max;
      vertices->at(i)[1] = vertices->at(i)[1] / max;
      vertices->at(i)[2] = vertices->at(i)[2] / max;
      tmp_normals.push_back( WMath::vec3(0.0f) );
    }
    // Calculating surface normals
    for( int i =0; i < vertexIndices->size(); i+=3 )
    {
      WMath::vec3 normal, u, v;
      int v0, v1, v2;
      v0 = vertexIndices->at(i);
      v1 = vertexIndices->at(i+1);
      v2 = vertexIndices->at(i+2);
      // p1 - p0, p2 - p1
      u = vertices->at( v1 ) - vertices->at( v0 );
      v = vertices->at( v2 ) - vertices->at( v0 );
      normal = WMath::cross(u, v);
      tmp_normals.at( v0 ) = tmp_normals.at( v0 ) + normal;
      tmp_normals.at( v1 ) = tmp_normals.at( v1 ) + normal;
      tmp_normals.at( v2 ) = tmp_normals.at( v2 ) + normal;
    }
    for( int i =0; i < vertexIndices->size(); i++ )
    {
      WMath::vec3 normal_normalized = WMath::normalize( tmp_normals.at( vertexIndices->at(i) ) );
      normals->push_back( normal_normalized );
    }
  }

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path)
    {
      std::cout << "Placeholder ModelHelper::CreateShader" << std::endl;

      std::string shader_file_content = ApplicationHelper::ReadFile( file_path );
      const GLchar *source_code = shader_file_content.c_str();

      // Create and compile the vertex shader
      GLuint shader = glCreateShader( shader_type );

      glShaderSource(shader, 1, &source_code, NULL);
      glCompileShader(shader);

      GLint status;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
      if( status != GL_TRUE )
      {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        //std::cout << buffer << std::endl;
        return 0; // CHECK!!!!!
      }
      else
      {
        return shader;
      }
    }

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader )
    {
      GLuint shader_program = glCreateProgram();
      glAttachShader( shader_program, vertex_shader );
      glAttachShader( shader_program, fragment_shader );
      glBindFragDataLocation( shader_program, 0, "outColor" );
      glLinkProgram( shader_program );
      return shader_program;
    }

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
        std::string fragment_shader_file_path )
    {
      GLuint vertex_shader = CreateShader( GL_VERTEX_SHADER,
          vertex_shader_file_path );
      GLuint fragment_shader = CreateShader( GL_FRAGMENT_SHADER,
          fragment_shader_file_path );
      return CreateShaderProgram( vertex_shader, fragment_shader );
    }


  }

}
