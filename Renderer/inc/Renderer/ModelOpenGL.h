#ifndef __WHITE_MODELOPENGL__
#define __WHITE_MODELOPENGL__

#include <iostream>
#include <string>
#include "Renderer/Model.h"
#include "Renderer/ModelHelper.h"
#include "WMath/WMath.h"
#include "ApplicationHelper.h"

class ModelOpenGL : public Model
{
  private:
    GLuint vao, vbo, shader_program;
    void setVertexAttribute( GLuint shader_program,
                              std::string attrib_name );
  public:
    ModelOpenGL( ModelFileType model_file_type, std::string file_path );
    void draw();
    void translate( WMath::vec3 vector );
    void scale( WMath::vec3 vector );
    void rotate( float degrees, WMath::vec3 vector );
};

#endif
