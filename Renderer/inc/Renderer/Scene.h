#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Input/Input.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Light.h"
#include "Renderer/Window.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "Renderer/Helpers/CameraHelper.h"

class Scene
{
  private:
    std::string name;
    std::vector< std::shared_ptr<Model> > models;
    std::vector<Light> lights;
    std::shared_ptr<Camera> camera;
    void updateLightsForShader( std::shared_ptr<Shader> shader );
    void updateCameraForShader( std::shared_ptr<Shader> shader );
  public:
    Scene( std::string name );
    void update();
    void addModel( std::shared_ptr<Model> model );
    void removeModel( std::shared_ptr<Model> model );
    void addLight( Light light );
    void updateLights();
    void setCamera( std::shared_ptr<Camera> camera );
    void updateCamera();
    // getters
    std::vector< std::shared_ptr<Model> >* getModels()
      { return &this->models; }
    std::shared_ptr<Camera> getCamera() { return this->camera; }
};

#endif
