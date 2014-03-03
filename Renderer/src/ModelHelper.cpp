#include <ModelHelper.h>

namespace ModelHelper
{

  void ImportOBJ()
  {
    std::cout << "Placeholder ModelHelper::ImportOBJ" << std::endl;
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
