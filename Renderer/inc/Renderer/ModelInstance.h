#ifndef __RENDERER_MODELINSTANCE__
#define __RENDERER_MODELINSTANCE__

#include <vector>
#include <memory>
#include "Renderer/Mesh.h"
#include "Renderer/ModelData.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "WMath/WMath.h"

class ModelInstance
{
  private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<ModelData> model_data;
    std::shared_ptr<Texture> texture;
    WMath::mat4 transform, translate, rotate, scale;
  public:
    ModelInstance( std::shared_ptr<Mesh> mesh );
    void update();

    // setters
    void setShader( std::shared_ptr<Shader> shader );
    void setTexture( std::shared_ptr<Texture> texture )
      { this->texture = texture; }

    void setModelData( std::shared_ptr<ModelData> model_data )
      { this->model_data = model_data; }

    // getters
    std::shared_ptr<Mesh> getMesh() { return this->mesh; };
    std::shared_ptr<Shader> getShader( ) { return this->shader; };

    WMath::mat4* getTransformM();
    WMath::mat4* getTranslateM() { return &this->translate; };
    WMath::mat4* getRotateM() { return &this->rotate; };
    WMath::mat4* getScaleM() { return &this->scale; };
};

#endif
