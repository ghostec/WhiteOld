#ifndef __RENDERER_MODEL__
#define __RENDERER_MODEL__

#include <vector>
#include <memory>
#include <string>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
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
    std::string name;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<ModelData> model_data;
    std::shared_ptr<Texture> texture;
    ModelType model_type;
  public:
    Model( std::string name, std::shared_ptr<Mesh> mesh,
        ModelType model_type = MODEL_3D );
    void use(); void unuse();
    void setTransform( WMath::mat4* t );
    // setters
    void setShader( std::shared_ptr<Shader> shader );
    void setTexture( std::shared_ptr<Texture> texture )
      { this->texture = texture; }
    void setModelData( std::shared_ptr<ModelData> model_data )
      { this->model_data = model_data; }
    // getters
    std::string getName() { return this->name; }
    std::shared_ptr<Mesh> getMesh() { return this->mesh; };
    std::shared_ptr<Shader> getShader() { return this->shader; };
    std::shared_ptr<Texture> getTexture() { return this->texture; };
    ModelType getModelType() { return this->model_type; }
    WMath::vec3 getDimensions();
};

#endif
