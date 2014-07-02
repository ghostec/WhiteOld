#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

#include <vector>
#include <memory>
#include "Renderer/ModelAsset.h"
#include "WMath/WMath.h"

class ModelInstance
{
  private:
    std::shared_ptr<ModelAsset> model_asset;
    std::shared_ptr<Shader> shader;
    WMath::mat4 transform, translate, rotate, scale;
    int picking_id;
    float opacity;
    WMath::vec3 color;
    void updateTransform
      ( std::shared_ptr<Shader> shader );
    void updateOpacity
      ( std::shared_ptr<Shader> shader );
  public:
    ModelInstance( std::shared_ptr<ModelAsset> model_asset );
    void setShader( std::shared_ptr<Shader> shader );
    void draw();
    void setColor( WMath::vec3 color );
    void setOpacity( float opacity );
    // getters
    std::shared_ptr<ModelAsset> getModelAsset() { return this->model_asset; };
    WMath::mat4* getTransformM();
    WMath::mat4* getTranslateM()
      { return &this->translate; };
    WMath::mat4* getRotateM() { return &this->rotate; };
    WMath::mat4* getScaleM() { return &this->scale; };
    std::shared_ptr<Shader> getShader() { return this->shader; };
    int getPickingId() { return this->picking_id; };
};

#endif
