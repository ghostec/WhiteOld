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
    GLuint texture;
    // Model
    std::vector< Shader* > shaders;
    int vertices_count;
  public:
    ModelAsset( std::string file_path );
    ModelAsset( std::vector< WMath::vec3 > vertices,
                std::vector< WMath::vec3 > uvs,
                std::vector< WMath::vec3 > normals,
                std::vector< std::array<GLushort, 3> > elements );
    void addShader( Shader* shader );
    void configureShader( Shader* shader );
    void setTexture( std::string name, Shader* shader );
    void before_draw( );
    void after_draw( );
    void drawWithShaders( std::vector< Shader* >* shaders );
    void draw( std::vector< Shader* >* instance_shaders );
    std::vector< Shader* >* getShaders() { return &this->shaders; };
};

#endif
