#ifndef __RENDERER_MOUSEPICKINGOPENGL__
#define __RENDERER_MOUSEPICKINGOPENGL__

#include <vector>
#include <GL/glew.h>
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "Input/Input.h"
#include "WMath/WMath.h"
#include "Helpers/Observable.h"

class Scene;

class MousePicking
{
  private:
    GLuint frame_buffer, frame_buffer_tex, render_buffer;
    Shader* shader;
    Scene* scene;
  public:
    MousePicking( Scene* scene );
    void draw_picker_colours();
    int getIdForPosition();
};

#endif
