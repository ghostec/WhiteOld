#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "Input/Input.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/ModelInstance.h"
#include "Renderer/Light.h"
#include "Renderer/Helpers/ShaderHelper.h"

class Scene
{
  private:
    std::map< std::shared_ptr<ModelAsset>, int >  model_assets;
    std::vector< std::shared_ptr<ModelInstance> > model_instances;
    std::vector< std::shared_ptr<Light> >         lights;
    std::shared_ptr<Camera>                       camera;
    void updateLightsForShaders
      ( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > shaders );
    void updateCameraForShaders
      ( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > shaders );
  public:
    void draw();
    void addModel( std::shared_ptr<ModelInstance> model_instance );
    void addLight( std::shared_ptr<Light> light );
    void updateLights();
    void setCamera( std::shared_ptr<Camera> camera );
    void updateCamera();
    // getters
    std::shared_ptr< std::vector< std::shared_ptr<ModelInstance> > >
      getModelInstances()
    {
      return std::make_shared< std::vector< std::shared_ptr<ModelInstance> > >
        ( this->model_instances );
    };
    std::shared_ptr<Camera> getCamera() { return this->camera; };
    std::shared_ptr<ModelInstance> getModelInstanceWithId( int id );
};

#endif
