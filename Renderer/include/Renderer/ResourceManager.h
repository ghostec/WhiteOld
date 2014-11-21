#ifndef __RENDERER_RESOURCEMANAGER__
#define __RENDERER_RESOURCEMANAGER__

#include <map>
#include <string>
#include <memory>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Renderer/ModelData.h"
#include "Renderer/GUIElement.h"
#include <typeinfo>

template<typename T>
using ResourceMap = std::map< std::string, std::shared_ptr<T> >;

class ResourceManager
{
  private:
    ResourceMap<Shader> shader;
    ResourceMap<Texture> texture;
    ResourceMap<Mesh> mesh;
    ResourceMap<Model> model;
    ResourceMap<Material> material;
  public:
    void addShader( std::string name, std::shared_ptr<Shader> shader )
      { this->shader[name] = shader; }

    void addTexture( std::string name, std::shared_ptr<Texture> texture )
      { this->texture[name] = texture; }

    void addMaterial( std::string name, std::shared_ptr<Material> material )
    {
      this->material[ name ] = material;
    }

    void addMesh( std::string name,
      std::shared_ptr<Mesh> mesh )
      { this->mesh[name] = mesh; }

    void addModel( std::string name,
      std::shared_ptr<Model> model )
      { this->model[name] = model; }

    std::shared_ptr<Shader> getShader( std::string name )
      { return this->shader[name]; }

    std::shared_ptr<Texture> getTexture( std::string name )
      { return this->texture[name]; }

    std::shared_ptr<Material> getMaterial( std::string name )
      { return this->material[ name ]; }

    std::shared_ptr<Mesh> getMesh( std::string name )
      { return this->mesh[name]; }

    std::shared_ptr<Model> getModel( std::string name )
      { return this->model[name]; }
};

#endif
