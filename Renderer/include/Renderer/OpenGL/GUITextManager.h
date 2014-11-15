#ifndef __WHITE_RENDERER_OPENGL_GUITEXTMANAGER__
#define __WHITE_RENDERER_OPENGL_GUITEXTMANAGER__

#include <iostream>
#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Renderer/Texture.h"
#include "Renderer/GUIText.h"

class GUITextManager
{
  private:
    FT_Library ft;
    std::vector< std::shared_ptr<GUITextFont> > fonts;
  public:
    GUITextManager();
    void loadFont( std::string name );
    // setters
    // getters
    std::shared_ptr<GUITextFont> getFont( std::string name );
};

#endif
