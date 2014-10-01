#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include "Input/Input.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/Model.h"
#include "Renderer/Light.h"
#include "Renderer/Window.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "Renderer/Helpers/CameraHelper.h"

class Scene
{
  private:
    std::string name;
    std::vector<Light> lights;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<SceneGraph> scene_graph;
    void updateLightsForShader( std::shared_ptr<Shader> shader );
    void updateCameraForShader( std::shared_ptr<Shader> shader );
  public:
    Scene( std::string name );
    void update();
    void addLight( Light light );
    // getters
    std::shared_ptr<Camera> getCamera() { return this->camera; }
    std::shared_ptr<SceneGraph> getSceneGraph() { return this->scene_graph; }
    // setters
    void setCamera( std::shared_ptr<Camera> camera );
    void setSceneGraph( std::shared_ptr<SceneGraph> scene_graph );
};

#endif
