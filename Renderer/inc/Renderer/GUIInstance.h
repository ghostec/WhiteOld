#ifndef __RENDERER_GUIINSTANCE__
#define __RENDERER_GUIINSTANCE__

#include "Renderer/ModelInstance.h"
#include "Renderer/GUIAsset.h"

class GUIInstance
{
  private:
    GUIAsset* gui_asset;
    ModelInstance* model_instance;
  public:
    GUIInstance( GUIAsset* gui_asset, float percent, float ar );
    void setState( GUI_STATE state );
    void translate( float x, float y );
    ModelInstance* getModelInstance() { return this->model_instance; };
};

#endif