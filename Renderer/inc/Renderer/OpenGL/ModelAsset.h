#ifndef __RENDERER_MODELASSETOPENGL__
#define __RENDERER_MODELASSETOPENGL__

#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <SOIL/SOIL.h>
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

typedef enum ModelAssetType
{
  MODEL_ASSET_2D, MODEL_ASSET_3D
} ModelAssetType;

class ModelAsset
{
  private:
    GLuint vao, vbo;
    std::shared_ptr<Texture> texture;
    std::vector< std::shared_ptr<Shader> > shaders;
    int vertices_count;
    ModelAssetType model_asset_type;
  public:
    ModelAsset( std::string file_path, ModelAssetType model_asset_type );
    ModelAsset( std::vector< WMath::vec3 > vertices,
      std::vector< WMath::vec3 > uvs,
      std::vector< WMath::vec3 > normals,
      std::vector< std::array<GLushort, 3> > elements,
      ModelAssetType model_asset_type );
    void addShader( std::shared_ptr<Shader> shader );
    void configureShader( std::shared_ptr<Shader> shader );
    void setTexture( std::shared_ptr<Texture> texture );
    void before_draw();
    void after_draw();
    void drawWithShaders
      ( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > shaders );
    void draw
      ( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > 
          instance_shaders );
    std::shared_ptr< std::vector< std::shared_ptr<Shader> > > getShaders() 
      { return std::make_shared< std::vector< std::shared_ptr<Shader> > >
          ( this->shaders ); };
};

#endif
