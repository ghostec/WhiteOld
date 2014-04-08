#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include <string>
#include "Renderer/Model.h"
#include "Renderer/ModelHelper.h"
#include "Renderer/Camera.h"
#include "Renderer/ShaderGLSL.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "ApplicationHelper.h"

class Model
{
  private:
    // OpenGL
    GLuint vao, vbo;
    ShaderGLSL shader;
    void setVertexAttribute( GLuint shader_program,
                              std::string attrib_name );
    void setUniformMatrix4fv( std::string name, const GLfloat *value );
    // Model
    void before_draw();
    void after_draw();
  public:
    ModelCommon model_data;
    Model( std::string file_path );
    void draw();
    void translate( WMath::vec3 vector );
    void scale( WMath::vec3 vector );
    void rotate( float degrees );
};

#endif
