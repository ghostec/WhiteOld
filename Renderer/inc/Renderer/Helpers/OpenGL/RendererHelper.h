#ifndef __RENDERER_HELPERS_OPENGL_RENDERERHELPER__
#define __RENDERER_HELPERS_OPENGL_RENDERERHELPER__

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Renderer/Window.h"

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer = 0 );
  void drawSGNode( std::shared_ptr<SGNode> sg_node );
  void drawSceneGraph( std::shared_ptr<SceneGraph> scene_graph );
}

#endif
