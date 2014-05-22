#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

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
    WMath::mat4 transform;
    GLenum DRAW_MODE;
  public:
    Movable moves;
    ModelInstance( ModelAsset* model_asset, GLenum DRAW_MODE );
    void draw();
    void move();
    // getters
    ModelAsset* getModelAsset() { return this->model_asset; };
    WMath::mat4* getTransform() { return &this->transform; };
};

#endif
