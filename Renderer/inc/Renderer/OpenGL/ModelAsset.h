#ifndef __RENDERER_MODELASSETOPENGL__
#define __RENDERER_MODELASSETOPENGL__

#include <iostream>
#include <string>
#include <array>
#include <SOIL/SOIL.h>
#include "Renderer/ModelAsset.h"
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"
#include "Renderer/OpenGL/Shader.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

class ModelAsset
{
  private:
    // OpenGL
    GLuint vao, vbo;
    Shader shader;
    void setVertexAttribute( GLuint shader_program,
                              std::string attrib_name );
    void setUniformMatrix4fv( std::string name, const GLfloat *value );
    // Model
    int vertices_count;
    void before_draw();
    void after_draw();
  public:
    ModelAsset( std::string file_path );
    void draw();
    Shader* getShader() { return &this->shader; };
};

#endif
