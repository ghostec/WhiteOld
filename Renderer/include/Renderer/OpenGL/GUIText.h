#ifndef __WHITE_RENDERER_OPENGL_GUITEXT__
#define __WHITE_RENDERER_OPENGL_GUITEXT__

#include <memory>
#include <string>
#include <vector>
#include "Renderer/Window.h"
#include "Renderer/GUIElement.h"

struct GUITextFont
{
  float atlas_width, atlas_height;
  std::string name;
  std::shared_ptr<Texture> texture_atlas;

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
    std::shared_ptr<GUIElement> parent, gui_element;
    std::shared_ptr<GUITextFont> font;
  public:
    GUIText( std::string name, std::shared_ptr<GUITextFont> font,
       std::string text = "" );
    void update();
    // setters
    void setText( std::string text );
    void setFont( std::shared_ptr<GUITextFont> font );
    // getters
    std::string getName() { return this->name; }
    std::string getText() { return this->text; }
    std::shared_ptr<GUIElement> getGUIElement() { return this->gui_element; }
};

#endif
