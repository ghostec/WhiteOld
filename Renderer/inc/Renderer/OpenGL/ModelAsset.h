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

typedef struct ModelAssetData
{
  std::vector< WMath::vec3 > vertices, uvs, normals;
  std::vector< std::array<GLushort, 3> > elements;
} ModelAssetData;

typedef enum ModelAssetType
{
  MODEL_ASSET_2D, MODEL_ASSET_3D
} ModelAssetType;

class ModelAsset
{
  private:
    GLuint vao, vbo;
    std::shared_ptr<Texture> texture;
    int vertices_count;
    ModelAssetType model_asset_type;
  public:
    ModelAsset( std::string file_path, ModelAssetType type );
    ModelAsset( ModelAssetData data, ModelAssetType type );
    void setTexture( std::shared_ptr<Texture> texture );
    void ModelAsset::configureShader( std::shared_ptr<Shader> shader );
    void before_draw( std::shared_ptr<Shader> shader );
    void after_draw();
    void draw( std::shared_ptr<Shader> shader );
};

#endif
