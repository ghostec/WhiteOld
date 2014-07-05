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

typedef enum GUIType
{
  DRAWNABLE, CONTAINER
} GUIType;

class GUIElement
{
  private:
    std::map< std::string, GUIState > state;
    std::shared_ptr<Model> model;
    std::string current_state;
    WMath::vec2 dimensions;
    std::shared_ptr<GUIElement> parent;
    GUIType gui_type;

    void constructorTail
      ( std::shared_ptr<Mesh> mesh, float ar, WMath::vec2 parent_dimensions,
      WMath::vec2 offset, WMath::vec2 offset_percent, float parent_percent );
  public:
    GUIElement
      ( std::shared_ptr<Mesh> mesh, std::shared_ptr<GUIElement> parent,
      float parent_percent, WMath::vec2 offset, WMath::vec2 offset_percent,
      GUIType gui_type );
    GUIElement
      ( std::shared_ptr<Mesh> mesh, WMath::vec2 dimensions, WMath::vec2 offset,
      WMath::vec2 offset_percent, GUIType gui_type );
    void setState( std::string name );
    void setState( std::string name, GUIState state );
    void translate( float x, float y );
    // getters
    WMath::vec2 getDimensions() { return this->dimensions; }
    std::shared_ptr<Model> getModel( ) { return this->model; };
    GUIType getGUIType() { return this->gui_type; }
};

#endif