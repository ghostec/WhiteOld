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

class GUIElement : public std::enable_shared_from_this<GUIElement>
{
  private:
    std::shared_ptr<GUIElement> parent;
    std::vector< std::shared_ptr<GUIElement> > child;
    std::map< std::string, GUIState > state;
    std::shared_ptr<Model> model;
    std::string current_state;
    GUIType gui_type;
    bool dirty;
    WMath::vec2 dimensions, offset, offset_percent;
    float ratio, parent_percent;

    float getPropagatedParentPercent();
    float getPropagatedAR();
  public:
    GUIElement
      ( std::shared_ptr<Mesh> mesh, std::shared_ptr<GUIElement> parent,
      GUIType gui_type );
    void update();
    void addChild( std::shared_ptr<GUIElement> child );
    void setRatio( float ratio ) { this->ratio = ratio; this->dirty = true; }
    void setOffset( WMath::vec2 offset );
    void addOffset( WMath::vec2 offset );
    void setOffsetPercent( WMath::vec2 offset_percent );
    void addOffsetPercent( WMath::vec2 offset_percent );
    void setParentPercent( float parent_percent );
    void addParentPercent( float parent_percent );
    void setState( std::string name );
    void setState( std::string name, GUIState state );
    void translate( float x, float y );
    // getters
    WMath::vec2 getDimensions() { return this->dimensions; }
    std::shared_ptr<Model> getModel() { return this->model; };
    std::shared_ptr<GUIElement> getParent() { return this->parent; }
    GUIType getGUIType() { return this->gui_type; }
    bool isDirty() { return this->dirty; }
};

#endif