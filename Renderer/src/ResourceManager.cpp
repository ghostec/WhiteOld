#include "Renderer/ResourceManager.h"

void ResourceManager::addShader(  std::shared_ptr<Shader> shader,
                                  std::string name )
{
  this->shaders[name] = shader;
}
void ResourceManager::addTexture( std::shared_ptr<Texture> texture,
                                  std::string name )
{
  this->textures[name] = texture;
}

void ResourceManager::addModelAsset(  std::shared_ptr<ModelAsset> model_asset,
                                      std::string name )
{
  this->model_assets[name] = model_asset;
}

void ResourceManager::addModelInstance( std::shared_ptr<ModelInstance> model_instance,
                                        std::string name )
{
  this->model_instances[name] = model_instance;
}

std::shared_ptr<Shader> ResourceManager::getShader( std::string name )
{
  return this->shaders[name];
}

std::shared_ptr<Texture> ResourceManager::getTexture( std::string name )
{
  return this->textures[name];
}

std::shared_ptr<ModelAsset> ResourceManager::getModelAsset( std::string name )
{
  return this->model_assets[name];
}

std::shared_ptr<ModelInstance> ResourceManager::getModelInstance( std::string name )
{
  return this->model_instances[name];
}