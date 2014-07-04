#ifndef __RENDERER_MODEL__
#define __RENDERER_MODEL__

#include <vector>
#include <memory>
#include "Renderer/Mesh.h"
#include "Renderer/ModelData.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "WMath/WMath.h"

typedef enum ModelType
{
  MODEL_2D, MODEL_3D
} ModelType;

class Model
{
  private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<ModelData> model_data;
    std::shared_ptr<Texture> texture;
    WMath::mat4 transform, translate, rotate, scale;
    ModelType model_type;
  public:
    Model( std::shared_ptr<Mesh> mesh, ModelType model_type = MODEL_3D );
    void update();

    // setters
    void setShader( std::shared_ptr<Shader> shader );
    void setTexture( std::shared_ptr<Texture> texture )
      { this->texture = texture; }

    void setModelData( std::shared_ptr<ModelData> model_data )
      { this->model_data = model_data; }

    // getters
    std::shared_ptr<Mesh> getMesh() { return this->mesh; };
    std::shared_ptr<Shader> getShader() { return this->shader; };
    ModelType getModelType() { return this->model_type; }

    WMath::mat4* getTransformM();
    WMath::mat4* getTranslateM() { return &this->translate; };
    WMath::mat4* getRotateM() { return &this->rotate; };
    WMath::mat4* getScaleM() { return &this->scale; };
};

#endif
