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
    std::vector< std::shared_ptr<Shader> > shaders;
    WMath::mat4 transform, translate, rotate, scale;
    int picking_id;
    float opacity;
    WMath::vec3 color;
    void updateTransform
      ( std::vector< std::shared_ptr<Shader> >* shaders );
    void updateOpacity
      ( std::vector< std::shared_ptr<Shader> >* shaders );
  public:
    ModelInstance( std::shared_ptr<ModelAsset> model_asset );
    void addShader( std::shared_ptr<Shader> shader );
    void draw();
    void setColor( WMath::vec3 color );
    void setOpacity( float opacity );
    // getters
    std::shared_ptr<ModelAsset> getModelAsset() { return this->model_asset; };
    WMath::mat4* getTransformM();
    WMath::mat4* getTranslateM()
      { return &this->translate; };
    WMath::mat4* getRotateM()
      { return &this->rotate; };
    WMath::mat4* getScaleM()
      { return &this->scale; };
    std::vector< std::shared_ptr<Shader> >* getShaders()
      { return &this->shaders; };
    int getPickingId() { return this->picking_id; };
};

#endif
