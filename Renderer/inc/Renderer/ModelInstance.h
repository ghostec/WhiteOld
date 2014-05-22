#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

#include <vector>
#include "Renderer/ModelAsset.h"

typedef struct Movable_
{
  bool ARROW_UP = false;
  bool ARROW_DOWN = false;
} Movable;

class ModelInstance
{
  private:
    ModelAsset* model_asset;
    std::vector< Shader* > shaders;
    WMath::mat4 transform;
  public:
    Movable moves;
    ModelInstance( ModelAsset* model_asset );
    void addShader( Shader* shader );
    void draw();
    void move();
    // getters
    ModelAsset* getModelAsset() { return this->model_asset; };
    WMath::mat4* getTransform() { return &this->transform; };
    std::vector< Shader* >* getShaders() { return &this->shaders; };
};

#endif
