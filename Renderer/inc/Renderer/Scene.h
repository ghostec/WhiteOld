#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "Input/Input.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Light.h"
#include "Renderer/Helpers/ShaderHelper.h"

class Scene
{
  private:
    std::map< std::shared_ptr<Mesh>, int >  model_assets;
    std::vector< std::shared_ptr<Model> > models;
    std::vector< std::shared_ptr<Light> > lights;
    std::shared_ptr<Camera> camera;
    void updateLightsForShader( std::shared_ptr<Shader> shader );
    void updateCameraForShader( std::shared_ptr<Shader> shader );
  public:
    void update();
    void addModel( std::shared_ptr<Model> model_instance );
    void addLight( std::shared_ptr<Light> light );
    void updateLights();
    void setCamera( std::shared_ptr<Camera> camera );
    void updateCamera();
    // getters
    std::vector< std::shared_ptr<Model> >* getModels()
      { return &this->models; }
    std::shared_ptr<Camera> getCamera() { return this->camera; }
};

#endif
