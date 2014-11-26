#ifndef __WHITE_RENDERER_OPENGL_GUITEXT__
#define __WHITE_RENDERER_OPENGL_GUITEXT__

#include <memory>
#include <string>
#include <vector>
#include "Renderer/Viewport.h"
#include "Renderer/Window.h"
#include "Renderer/GUIElement.h"

struct GUITextFont
{
  float atlas_width, atlas_height, font_size;
  std::string name;
  std::shared_ptr< Material > material_atlas;

  struct character_info {
    float ax; // advance.x
    float ay; // advance.y

    float bw; // bitmap.width;
    float bh; // bitmap.rows;

    float bl; // bitmap_left;
    float bt; // bitmap_top;

    float tx; // x offset of glyph in texture coordinates
  } c[128];
};

class GUIText
{
  private:
    std::string name, text;
    std::shared_ptr<Viewport> viewport;
    WMath::vec2 cached_viewport_dimensions;
    std::shared_ptr<GUIElement> parent, gui_element;
    std::shared_ptr<GUITextFont> font;
    // methods
    void updateGUIElement();
  public:
    GUIText( std::string name, std::shared_ptr<GUITextFont> font,
      std::shared_ptr<Viewport> viewport, std::shared_ptr<GUIElement> parent,
      std::string text = "" );
    void update();
    void hide();
    void show();
    // setters
    void setText( std::string text );
    void setFont( std::shared_ptr<GUITextFont> font );
    // getters
    std::string getName() { return this->name; }
    std::string getText() { return this->text; }
    std::shared_ptr<GUIElement> getGUIElement() { return this->gui_element; }
};

#endif
