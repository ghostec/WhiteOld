#ifndef __RENDERER_GUIINSTANCE__
#define __RENDERER_GUIINSTANCE__

#include "Renderer/ModelInstance.h"
#include "Renderer/GUIAsset.h"

class GUIInstance
{
  private:
    GUIAsset* gui_asset;
    ModelInstance* model_instance;
    float width, height;
  public:
    GUIInstance( GUIAsset* gui_asset, float width, float height );
    GUIInstance( GUIAsset* gui_asset, GUIInstance* parent, float percent );
    void setState( GUI_STATE state );
    void translate( float x, float y );
    ModelInstance* getModelInstance() { return this->model_instance; };
    // getters
    float getWidth() { return this->width; };
    float getHeight( ) { return this->height; };
};

#endif