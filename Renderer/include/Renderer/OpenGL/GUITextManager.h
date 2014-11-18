#ifndef __WHITE_RENDERER_OPENGL_GUITEXTMANAGER__
#define __WHITE_RENDERER_OPENGL_GUITEXTMANAGER__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderer/Texture.h"
#include "Renderer/GUIElement.h"
#include "Renderer/GUIText.h"

class GUITextManager
{
  private:
    FT_Library ft;
    std::vector< std::shared_ptr<GUITextFont> > fonts;
    std::vector< std::shared_ptr<GUIText> > gui_texts;
  public:
    GUITextManager();   
    std::shared_ptr<GUITextFont> getGUITextFont( std::string name, float size );
    void update();
    std::shared_ptr<GUIText> makeGUIText( std::string name,
      std::string font_name, float font_size, std::string text,
      std::shared_ptr<GUIElement> parent, std::shared_ptr<Viewport> viewport );
    void addGUIText( std::shared_ptr<GUIText> gui_text );
    void removeGUIText( std::shared_ptr<GUIText> gui_text );
};

#endif
