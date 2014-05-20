#include "Renderer/Helpers/Model.h"

namespace ModelHelper
{
  void parseFaceOBJ(  std::istringstream& s,
                      std::vector< std::array<GLushort, 3> >& elements )
  {
    std::tr1::cmatch values;
    std::string text;

    std::tr1::regex rx_v( "([0-9]+)" );
    std::tr1::regex rx_vt( "([0-9]+)\/([0-9]+)" );
    std::tr1::regex rx_vn( "([0-9]+)\/\/([0-9]+)" );
    std::tr1::regex rx_vtn( "([0-9]+)\/([0-9]+)\/([0-9]+)" );

    for( int i = 0; i < 3; i++ )
    {
      s >> text;
      std::array<GLushort, 3> elem;
      if( std::regex_match( text, rx_v ) )
      {
        std::tr1::regex_search( text.c_str( ), values, rx_v );
        elem[0] = atoi( values[1].str( ).c_str( ) ) - 1;
      }
      else if( std::regex_match( text, rx_vt ) )
      {
        std::tr1::regex_search( text.c_str( ), values, rx_vt );
        elem[0] = atoi( values[1].str( ).c_str( ) ) - 1;
        elem[1] = atoi( values[2].str( ).c_str( ) ) - 1;
      }
      else if( std::regex_match( text, rx_vn ) )
      {
        std::tr1::regex_search( text.c_str( ), values, rx_vt );
        elem[0] = atoi( values[1].str( ).c_str( ) ) - 1;
        elem[2] = atoi( values[2].str( ).c_str( ) ) - 1;
      }
      else if( std::regex_match( text, rx_vtn ) )
      {
        std::tr1::regex_search( text.c_str( ), values, rx_vt );
        elem[0] = atoi( values[1].str( ).c_str( ) ) - 1;
        elem[1] = atoi( values[2].str( ).c_str( ) ) - 1;
        elem[2] = atoi( values[3].str( ).c_str( ) ) - 1;
      }
      elements.push_back( elem );
    }
  }

  void ImportOBJ( const char* filename, std::vector<WMath::vec3>& vertices,
                  std::vector<WMath::vec3>& uvs, 
                  std::vector<WMath::vec3>& normals,
                  std::vector< std::array<GLushort, 3> > &elements )
  {
    std::ifstream in( filename, std::ios::in );
    if( !in ) { std::cerr << "Cannot open " << filename << std::endl; exit( 1 ); }

    std::string line;
    while( getline( in, line ) ) 
    {
      if( line.substr( 0, 2 ) == "v " ) 
      {
        std::istringstream s( line.substr( 2 ) );
        WMath::vec3 v; s >> v[0]; s >> v[1]; s >> v[2];
        vertices.push_back( v );
      }
      if( line.substr( 0, 3 ) == "vt " )
      {
        std::istringstream s( line.substr( 3 ) );
        WMath::vec3 uv; s >> uv[0]; s >> uv[1]; uv[2] = 0.0f;
        uvs.push_back( uv );
      }
      else if( line.substr( 0, 2 ) == "f " ) 
      {
        std::istringstream s( line.substr( 2 ) );
        parseFaceOBJ( s, elements );
      }
      else if( line[0] == '#' ) { /* ignoring this line */ }
      else { /* ignoring this line */ }
    }

    float max = 0.0f;
    for( int i = 0; i < vertices.size( ); i++ )
      for( int j = 0; j < 3; j++ )
        if( vertices[i][j] > max ) max = vertices[i][j];
    for( int i = 0; i < vertices.size( ); i++ )
      for( int j = 0; j < 3; j++ )
        vertices[i][j] /= max;
  }

  std::vector< WMath::vec3 > 
    CalculateNormalsAveraged( std::vector< WMath::vec3 >& vertices,
                              std::vector < std::array<GLushort, 3> >& elements )
  {
    std::vector< WMath::vec3 > normals;
    std::vector< int > nb_seen;

    normals.resize( vertices.size( ), WMath::vec3( 0.0, 0.0, 0.0 ) );
    nb_seen.resize( vertices.size( ), 0 );
    for( int i = 0; i < elements.size( ); i += 3 )
    {
      GLushort ia = elements[i][0];
      GLushort ib = elements[i + 1][0];
      GLushort ic = elements[i + 2][0];
      WMath::vec3 normal = WMath::normalize( WMath::cross(
        WMath::vec3( vertices[ib] ) - WMath::vec3( vertices[ia] ),
        WMath::vec3( vertices[ic] ) - WMath::vec3( vertices[ia] ) ) );

      int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
      for( int j = 0; j < 3; j++ )
      {
        GLushort cur_v = v[j];
        nb_seen[cur_v]++;
        if( nb_seen[cur_v] == 1 )
        {
          normals[cur_v] = normal;
        }
        else
        {
          // average
          normals[cur_v][0] = normals[cur_v][0] * ( 1.0 - 1.0 / nb_seen[cur_v] ) + normal[0] * 1.0 / nb_seen[cur_v];
          normals[cur_v][1] = normals[cur_v][1] * ( 1.0 - 1.0 / nb_seen[cur_v] ) + normal[1] * 1.0 / nb_seen[cur_v];
          normals[cur_v][2] = normals[cur_v][2] * ( 1.0 - 1.0 / nb_seen[cur_v] ) + normal[2] * 1.0 / nb_seen[cur_v];
          normals[cur_v] = WMath::normalize( normals[cur_v] );
        }
      }
    }
    return normals;
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
