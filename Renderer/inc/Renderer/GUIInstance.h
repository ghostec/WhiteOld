#ifndef __RENDERER_GUIINSTANCE__
#define __RENDERER_GUIINSTANCE__

#include "Renderer/ModelInstance.h"
#include "Renderer/GUIAsset.h"

class GUIInstance
{
  private:
    std::shared_ptr<GUIAsset> gui_asset;
    std::shared_ptr<GUIInstance> parent;
    std::shared_ptr<ModelInstance> model_instance;
    float width, height;
  public:
    GUIInstance( std::shared_ptr<GUIAsset> gui_asset, float width, float height,
                  float offset_x, float offset_y,
                  float offset_x_percent, float offset_y_percent );
    GUIInstance( std::shared_ptr<GUIAsset> gui_asset, 
      std::shared_ptr<GUIInstance> parent, float percent,
      float offset_x, float offset_y,
      float offset_x_percent, float offset_y_percent );
    void translate( float x, float y );
    std::shared_ptr<ModelInstance> getModelInstance() 
      { return this->model_instance; };
    // getters
    float getWidth() { return this->width; };
    float getHeight( ) { return this->height; };
};

#endif