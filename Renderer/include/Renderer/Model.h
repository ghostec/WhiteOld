#ifndef __RENDERER_MODEL__
#define __RENDERER_MODEL__

#include <vector>
#include <memory>
#include <string>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
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
    std::string name;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<ModelData> model_data;
    std::shared_ptr<Material> material;
    ModelType model_type;
  public:
    Model( std::string name, std::shared_ptr<Mesh> mesh,
        ModelType model_type = MODEL_3D );
    void use(); void unuse();
    // setters
    void setShader( std::shared_ptr<Shader> shader );
    void setMaterial( std::shared_ptr<Material> m ) { this->material = m; }
    void setModelData( std::shared_ptr<ModelData> model_data )
      { this->model_data = model_data; }
    // getters
    std::string getName() { return this->name; }
    std::shared_ptr<Mesh> getMesh() { return this->mesh; };
    std::shared_ptr<Shader> getShader() { return this->shader; };
    std::shared_ptr<Material> getMaterial() { return this->material; };
    std::shared_ptr<ModelData> getModelData() { return this->model_data; }
    ModelType getModelType() { return this->model_type; }
    WMath::vec3 getDimensions();
};

#endif
