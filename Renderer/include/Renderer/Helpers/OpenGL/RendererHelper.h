#ifndef __RENDERER_HELPERS_OPENGL_RENDERERHELPER__
#define __RENDERER_HELPERS_OPENGL_RENDERERHELPER__

#include <memory>
#include <vector>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Viewport.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Renderer/Window.h"
#include "Renderer/Helpers/OpenGL/ShaderHelper.h"
#include "WMath/WMath.h"

namespace RendererHelper
{
  void updateViewport( Viewport* viewport );
  void drawSGNode( SGNode* n, Shader* custom_shader = nullptr );
  void drawSceneGraph( SceneGraph* scene_graph );
}

#endif
