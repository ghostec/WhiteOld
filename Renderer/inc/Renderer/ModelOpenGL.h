#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include <string>
#include "Renderer/Model.h"
#include "Renderer/ModelHelper.h"
#include "Renderer/Camera.h"
#include "Renderer/ShaderGLSL.h"
#include "WMath/WMath.h"
#include "ApplicationHelper.h"

class ModelOpenGL : public Model
{
  private:
    GLuint vao, vbo;
    ShaderGLSL shader;
    int vertices_count;
    void setVertexAttribute( GLuint shader_program,
                              std::string attrib_name );
    void setUniformMatrix4fv( std::string name, const GLfloat *value );
    void before_draw();
    void after_draw();
  public:
    WMath::mat4 transformation;
    ModelOpenGL( ModelFileType model_file_type, std::string file_path );
    void draw();
    void translate( WMath::vec3 vector );
    void scale( WMath::vec3 vector );
    void rotate( float degrees );
};

#endif
