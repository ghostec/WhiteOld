#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include "Model.h"
#include "ModelHelper.h"
#include "ApplicationHelper.h"

class ModelOpenGL : public Model
{
  private:
    GLuint vao, vbo, shader_program;
  public:
    ModelOpenGL( ModelFileType model_file_type, std::string file_path );
    void draw();
    void translate( Vector3 vector );
    void scale( Vector3 vector );
    void rotate( float degrees, Vector3 vector );
};

ModelOpenGL::ModelOpenGL( ModelFileType model_file_type,
                          std::string file_path )
{
  if( model_file_type == OBJ ) ModelHelper::ImportOBJ();

  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  glGenBuffers(1, &this->vbo);

  GLfloat vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f
  };

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint shader_program = ModelHelper::OpenGL::CreateShaderProgram(
                          "../shaders/vertex_shader.glsl",
                          "../shaders/fragment_shader.glsl" );

  // Link the vertex and fragment shader into a shader program
  glUseProgram(shader_program);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0); 
}

void ModelOpenGL::draw()
{
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ModelOpenGL::translate( Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::translate()" << std::endl;
}

void ModelOpenGL::scale( Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::scale()" << std::endl;
}

void ModelOpenGL::rotate( float degrees, Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::rotate()" << std::endl;
}

#endif
