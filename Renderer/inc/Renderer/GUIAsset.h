#ifndef __RENDERER_GUIASSET__
#define __RENDERER_GUIASSET__

#include "Renderer/ModelAsset.h"

typedef enum GUI_STATE
{
  GUI_NORMAL, GUI_HOVER, GUI_CLICK
} GUI_STATE;

class GUIAsset
{
  private:
    std::map< GUI_STATE, ModelAsset* > model_assets;
    Shader* shader;
  public:
    GUIAsset( float width, float height, std::string texture );
    ModelAsset* getModelAsset( GUI_STATE state );
};

#endif
