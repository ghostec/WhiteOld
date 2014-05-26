#ifndef __RENDERER_GUIASSET__
#define __RENDERER_GUIASSET__

#include "Renderer/ModelAsset.h"

class GUIAsset
{
  private:
    ModelAsset* model_asset;
    Shader* shader;
  public:
    GUIAsset( float width, float height );
    ModelAsset* getModelAsset() { return this->model_asset; };
};

#endif
