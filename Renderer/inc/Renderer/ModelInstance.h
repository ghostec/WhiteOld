#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

#include <vector>
#include <memory>
#include "Renderer/ModelAsset.h"
#include "WMath/WMath.h"

typedef struct
{
  std::vector< std::pair< std::string, float > > floats;
} ModelData;

class ModelInstance
{
  private:
    std::shared_ptr<ModelAsset> model_asset;
    std::shared_ptr<Shader> shader;
    WMath::mat4 transform, translate, rotate, scale;
    ModelData data;
    int picking_id;
    void updateTransform
      ( std::shared_ptr<Shader> shader );
  public:
    ModelInstance( std::shared_ptr<ModelAsset> model_asset );
    void setShader( std::shared_ptr<Shader> shader );
    void draw();
    void addFloat( std::string name, float f );
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
