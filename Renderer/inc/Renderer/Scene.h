#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <utility>
#include <vector>
#include "Input/Input.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/ModelInstance.h"
#include "Renderer/Light.h"

typedef std::pair< int, ModelAsset* > ModelAssetPair;

class Scene
{
  private:
    std::vector<ModelAssetPair> model_assets;
    std::vector<ModelInstance*> model_instances;
    std::vector<Light*> lights;
    Camera* camera;
    void updateLightsForShaders( std::vector< Shader* >* shaders );
    void updateCameraForShaders( std::vector< Shader* >* shaders );
  public:
    void draw();
    void addModel( ModelInstance* model_instance );
    void addLight( Light* light );
    void updateLights();
    void setCamera( Camera* camera );
    void updateCamera();
    // getters
    std::vector< ModelInstance* >* getModelInstances() 
      { return &this->model_instances; };
    Camera* getCamera() { return this->camera; };
    ModelInstance* getModelInstanceWithId( int id );
};

#endif
