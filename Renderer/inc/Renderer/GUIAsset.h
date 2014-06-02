#ifndef __RENDERER_GUIASSET__
#define __RENDERER_GUIASSET__

#include <map>
#include "Renderer/ModelAsset.h"

typedef enum GUI_STATE
{
  GUI_NORMAL, GUI_HOVER, GUI_CLICK
} GUI_STATE;

class GUIAsset
{
  private:
    std::map< GUI_STATE, std::shared_ptr<ModelAsset> > model_assets;
    std::shared_ptr<Shader> shader;
  public:
    GUIAsset( float width, float height, std::shared_ptr<Texture> texture );
    std::shared_ptr<ModelAsset> getModelAsset( GUI_STATE state );
};

#endif
