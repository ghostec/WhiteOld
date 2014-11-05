#ifndef __RENDERER_HELPERS_OPENGL_RENDERERHELPER__
#define __RENDERER_HELPERS_OPENGL_RENDERERHELPER__

#include <memory>
#include <vector>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Renderer/Window.h"
#include "WMath/WMath.h"

namespace RendererHelper
{
  void drawSGNode( SGNode* n,
     std::shared_ptr<Shader> custom_shader = nullptr );
  void drawSceneGraph( std::shared_ptr<SceneGraph> scene_graph );
}

#endif
