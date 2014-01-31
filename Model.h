#ifndef __WHITE_MODEL__
#define __WHITE_MODEL__

#include <iostream>
#include <string>
#include "Math.h"
#include "ModelHelper.h"

// Shader sources
const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "void main() {"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";
const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main() {"
    "   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";

typedef enum _ModelFileType { OBJ } ModelFileType;

class Model
{
  public:
    virtual void draw() = 0;
    virtual void translate( Vector3 vector ) = 0;
    virtual void scale( Vector3 vector ) = 0;
    virtual void rotate( float degrees, Vector3 vector ) = 0;
};

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

  // Create and compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Create and compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Link the vertex and fragment shader into a shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
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
