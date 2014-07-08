#ifndef __RENDERER_MOUSEPICKINGOPENGL__
#define __RENDERER_MOUSEPICKINGOPENGL__

#include <vector>
#include <memory>
#include <GL/glew.h>
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "Renderer/Helpers/RendererHelper.h"
#include "Renderer/Helpers/ShaderHelper.h"
#include "Input/Input.h"
#include "WMath/WMath.h"
#include "Helpers/Observable.h"

class MousePicking
{
  private:
    GLuint frame_buffer, frame_buffer_tex, render_buffer;
    std::shared_ptr<Shader> shader;
    Scene* scene;
  public:
    MousePicking();
    void setScene( Scene* scene );
    void draw_picker_colours();
    std::shared_ptr<Model> getIdForPosition( int x, int y );
};

#endif
