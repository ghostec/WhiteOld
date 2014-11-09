#include "Renderer/GUITextManager.h"

GUITextManager::GUITextManager()
{
  FT_Library ft;
  FT_Init_FreeType(&ft);

  FT_Face face;

  if(FT_New_Face(ft, "../assets/fonts/monaco.ttf", 0, &face)) {
    std::cout << "Could not open font" << std::endl;
  }
}
