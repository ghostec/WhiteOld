#ifndef __RENDERER_MOUSEPICKINGOPENGL__
#define __RENDERER_MOUSEPICKINGOPENGL__

#include <vector>
#include <GL/glew.h>
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "WMath/WMath.h"

class Scene;

class MousePicking
{
  private:
    GLuint frame_buffer, frame_buffer_tex, render_buffer;
    Shader* shader;
  public:
    MousePicking();
    void draw_picker_colours( Scene* scene );
    int getIdForPosition( int x, int y );
};

#endif
