#ifndef __RENDERER_GUIINSTANCE__
#define __RENDERER_GUIINSTANCE__

#include "Renderer/ModelInstance.h"
#include "Renderer/GUIAsset.h"

class GUIInstance
{
  private:
    ModelInstance* model_instance;
  public:
    GUIInstance( GUIAsset* gui_asset, float percent, float ar );
    void translate( float x, float y );
    ModelInstance* getModelInstance() { return this->model_instance; };
};

#endif