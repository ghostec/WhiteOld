#ifndef __RENDERER_HELPERS_OPENGL_RENDERERHELPER__
#define __RENDERER_HELPERS_OPENGL_RENDERERHELPER__

#include <memory>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SGNode.h"
#include "Renderer/Window.h"

typedef struct _PropagatedSGNodeData
{
  _PropagatedSGNodeData() : translate(0), scale(1), rotate() {};
  WMath::vec3 translate;
  WMath::vec3 scale;
  WMath::quaternion rotate;
} PropagatedSGNodeData;

typedef std::pair< std::shared_ptr<SGNode>, PropagatedSGNodeData > PropagatedSGNode;

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer = 0 );
  void drawSGNode( std::shared_ptr<SGNode> sg_node );
  void drawPropagatedSGNode( PropagatedSGNode propagated_node );
}

#endif
