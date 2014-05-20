#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include <string>
#include <array>
#include <SOIL/SOIL.h>
#include "Renderer/Model.h"
#include "Renderer/Helpers/Model.h"
#include "Renderer/Camera.h"
#include "Renderer/OpenGL/Shader.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

typedef struct Movable_
{
  bool ARROW_UP     = false;
  bool ARROW_DOWN   = false;
} Movable;

class Model
{
  private:
    // OpenGL
    GLuint vao, vbo;
    Shader shader;
    void setVertexAttribute( GLuint shader_program,
                              std::string attrib_name );
    void setUniformMatrix4fv( std::string name, const GLfloat *value );
    // Model
    void before_draw();
    void after_draw();
  public:
    ModelCommon model_data;
    Movable moves;
    Model( std::string file_path );
    void draw();
    void setView( WMath::mat4* view );
    void setProj( WMath::mat4* proj );
    void move();
};

#endif
