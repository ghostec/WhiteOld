#include "Renderer/Helpers/Model.h"

namespace ModelHelper
{
  void ImportOBJ( const char* filename, std::vector<WMath::vec4> &vertices, std::vector<WMath::vec3> &normals, std::vector<GLushort> &elements ) 
  {
    std::ifstream in( filename, std::ios::in );
    if( !in ) { std::cerr << "Cannot open " << filename << std::endl; exit( 1 ); }

    std::string line;
    while( getline( in, line ) ) {
      if( line.substr( 0, 2 ) == "v " ) {
        std::istringstream s( line.substr( 2 ) );
        WMath::vec4 v; s >> v[0]; s >> v[1]; s >> v[2]; v[3] = 1.0f;
        vertices.push_back( v );
      }
      else if( line.substr( 0, 2 ) == "f " ) {
        std::istringstream s( line.substr( 2 ) );
        GLushort a, b, c;
        s >> a; s >> b; s >> c;
        a--; b--; c--;
        elements.push_back( a ); elements.push_back( b ); elements.push_back( c );
      }
      else if( line[0] == '#' ) { /* ignoring this line */ }
      else { /* ignoring this line */ }
    }

    normals.resize( vertices.size( ), WMath::vec3( 0.0, 0.0, 0.0 ) );
    for( int i = 0; i < elements.size( ); i += 3 ) {
      GLushort ia = elements[i];
      GLushort ib = elements[i + 1];
      GLushort ic = elements[i + 2];
      WMath::vec3 normal = WMath::normalize( WMath::cross(
        WMath::vec3( vertices[ib] ) - WMath::vec3( vertices[ia] ),
        WMath::vec3( vertices[ic] ) - WMath::vec3( vertices[ia] ) ) );
      normals[ia] = normals[ib] = normals[ic] = normal;
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
        std::cout << buffer << std::endl;
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
