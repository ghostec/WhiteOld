#ifndef __RENDERER_MODELASSETOPENGL__
#define __RENDERER_MODELASSETOPENGL__

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <SOIL/SOIL.h>
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
    // Model
    std::vector< Shader* > shaders;
    int vertices_count;
    void before_draw();
    void after_draw();
    void drawForShaders( std::vector< Shader* >* shaders );
  public:
    ModelAsset( std::string file_path );
    void addShader( Shader* shader );
    void configureShader( Shader* shader );
    void draw( std::vector< Shader* >* instance_shaders );
    std::vector< Shader* >* getShaders() { return &this->shaders; };
};

#endif
