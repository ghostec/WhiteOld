#include "Renderer/GUITextManager.h"

GUITextManager::GUITextManager()
{
  FT_Init_FreeType(&this->ft);
}

void GUITextManager::loadFont( std::string name )
{
  FT_Face face;

  std::string path = "../assets/fonts/" + name + ".ttf";
  if(FT_New_Face(ft, path.c_str(), 0, &face)) {
    std::cout << "Could not open font" << std::endl;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  FT_GlyphSlot g = face->glyph;
  int w = 0;
  int h = 0;

  for(int i = 32; i < 128; i++)
  {
    if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
      std::cout << "Could not load character" << std::endl;
      continue;
    }

    w += g->bitmap.width;
    h = std::max(h, g->bitmap.rows);
  }

  std::shared_ptr<GUITextFont> gtf( new GUITextFont() );
  gtf->atlas_width = (float) w;
  gtf->atlas_height = (float) h;

  std::shared_ptr<Texture> texture
    ( new Texture( WMath::vec2( (float) w, (float) h ) ) );

  gtf->texture_atlas = texture;

  int x = 0;

  for(int i = 32; i < 128; i++)
  {
    if(FT_Load_Char(face, i, FT_LOAD_RENDER))
      continue;

    glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0,
        g->bitmap.width, g->bitmap.rows,
        GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

    gtf->c[i].ax = g->advance.x >> 6;
    gtf->c[i].ay = g->advance.y >> 6;

    gtf->c[i].bw = g->bitmap.width;
    gtf->c[i].bh = g->bitmap.rows;

    gtf->c[i].bl = g->bitmap_left;
    gtf->c[i].bt = g->bitmap_top;

    gtf->c[i].tx = (float) x / w;

    x += g->bitmap.width;
  }

  this->fonts[name] = gtf;
}

std::shared_ptr<GUITextFont> GUITextManager::getFont( std::string name )
{
  return this->fonts[name];
}
