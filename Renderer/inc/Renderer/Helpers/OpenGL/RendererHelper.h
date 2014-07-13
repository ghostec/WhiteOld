#ifndef __RENDERER_HELPERS_OPENGL_RENDERERHELPER__
#define __RENDERER_HELPERS_OPENGL_RENDERERHELPER__

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/Window.h"

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer = 0 );
}

#endif
