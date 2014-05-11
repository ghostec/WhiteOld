#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include <string>
#include "Renderer/Model.h"
#include "Renderer/Helpers/Model.h"
#include "Renderer/Camera.h"
#include "Renderer/OpenGL/Shader.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

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
    Model( std::string file_path );
    void draw();
    void translate( WMath::vec3 vector );
    void scale( WMath::vec3 vector );
    void rotate( float degrees );
    void setView( WMath::mat4 view );
    void setProj( WMath::mat4 proj );
};

#endif
