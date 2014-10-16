#ifndef __RENDERER_MOUSEPICKINGOPENGL__
#define __RENDERER_MOUSEPICKINGOPENGL__

#include <queue>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "Renderer/Helpers/RendererHelper.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "Renderer/SGNode.h"
#include "Renderer/Viewport.h"
#include "Input/Input.h"
#include "WMath/WMath.h"
#include "Helpers/Observable.h"

class MousePicking
{
  private:
    GLuint frame_buffer, frame_buffer_tex, render_buffer;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Viewport> viewport;
    WMath::vec2 viewport_dimensions;
    int node_count;
    // Private Methods
    void drawViewport( Viewport* viewport );
    void drawScene( Scene* scene, ViewportCachedData viewport_cached_data );
  public:
    MousePicking();
    void reset();
    void setViewport( std::shared_ptr<Viewport> v ) { this->viewport = v; }
    std::shared_ptr<SGNode> pick();
};

extern MousePicking* active_mouse_picking;

#endif
