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

typedef struct _PropagatedSGNode
{
  _PropagatedSGNode() : translate(0), scale(1), rotate() {}
  WMath::vec3 translate, scale;
  WMath::quaternion rotate;
  std::shared_ptr<SGNode> sg_node;
} PropagatedSGNode;

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer = 0 );
  void drawSGNode( std::shared_ptr<SGNode> sg_node );
  void drawSceneGraph( std::shared_ptr<SceneGraph> scene_graph );
}

#endif
