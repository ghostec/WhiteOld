#ifndef __RENDERER_RESOURCEMANAGER__
#define __RENDERER_RESOURCEMANAGER__

#include <map>
#include <string>
#include <memory>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/ModelInstance.h"

template<typename T>
using ResourceMap = std::map< std::string, std::shared_ptr<T> >;

class ResourceManager
{
  private:
    ResourceMap<Shader> shaders;
    ResourceMap<Texture> textures;
    ResourceMap<ModelAsset> model_assets;
    ResourceMap<ModelInstance> model_instances;
  public:
    void addShader( std::shared_ptr<Shader> shader, std::string name );
    void addTexture( std::shared_ptr<Texture> texture, std::string name );
    void addModelAsset( std::shared_ptr<ModelAsset> model_asset,
                        std::string name );
    void addModelInstance(  std::shared_ptr<ModelInstance> model_instance,
                            std::string name );
    std::shared_ptr<Shader> getShader( std::string name );
    std::shared_ptr<Texture> getTexture( std::string name );
    std::shared_ptr<ModelAsset> getModelAsset( std::string name );
    std::shared_ptr<ModelInstance> getModelInstance( std::string name );
};

#endif
