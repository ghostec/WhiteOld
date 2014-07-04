#ifndef __RENDERER_GUIELEMENT__
#define __RENDERER_GUIELEMENT__

#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

typedef struct GUIState
{
  std::shared_ptr<Shader> shader;
  std::shared_ptr<Texture> texture;
  // TODO: add transition effect
} GUIState;

class GUIElement
{
  private:
    std::map< std::string, GUIState > state;
    std::shared_ptr<Model> model;
    std::string current_state;
    float width, height;
  public:
    GUIElement( float width, float height, float offset_x, float offset_y,
      float offset_x_percent, float offset_y_percent );
    GUIElement( std::shared_ptr<GUIElement> parent, float percent,
      float offset_x, float offset_y,
      float offset_x_percent, float offset_y_percent );
    void setState( std::string name, std::shared_ptr<Model> model );
    void translate( float x, float y );
    // getters
    float getWidth() { return this->width; };
    float getHeight() { return this->height; };
    std::shared_ptr<Model> getModel( ) { return this->model; };
};

#endif