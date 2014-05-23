#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

#include <vector>
#include "Renderer/ModelAsset.h"

class ModelInstance
{
  private:
    ModelAsset* model_asset;
    std::vector< Shader* > shaders;
    WMath::mat4 transform;
    int picking_id;
    void updateTransform( std::vector< Shader* >* shaders );
  public:
    ModelInstance( ModelAsset* model_asset );
    void addShader( Shader* shader );
    void draw();
    // getters
    ModelAsset* getModelAsset() { return this->model_asset; };
    WMath::mat4* getTransform() { return &this->transform; };
    std::vector< Shader* >* getShaders() { return &this->shaders; };
    int getPickingId() { return this->picking_id; };
};

#endif
