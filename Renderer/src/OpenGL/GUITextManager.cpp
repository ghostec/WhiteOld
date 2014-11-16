#include "..\..\include\Renderer\OpenGL\GUITextManager.h"

GUITextManager::GUITextManager()
{
  if( FT_Init_FreeType( &this->ft ) )
    std::cout << "Could not init freetype library" << std::endl;
}

void GUITextManager::loadFont( std::string name )
{
  FT_Face face;

  std::string path = "../assets/fonts/" + name + ".ttf";

  if( FT_New_Face( ft, path.c_str(), 0, &face ) )
    std::cout << "Could not open font" << std::endl;

  FT_Set_Pixel_Sizes( face, 0, 48 );

  FT_GlyphSlot g = face->glyph;

  int w = 0;
  int h = 0;

  for( int i = 32; i < 128; i++ )
  {
    if( FT_Load_Char( face, i, FT_LOAD_RENDER ) )
      std::cout << "Loading character %c failed!" << std::endl;

    w += g->bitmap.width;
    h = std::max( h, g->bitmap.rows );
  }

  std::shared_ptr<Texture> texture_atlas
    ( new Texture( WMath::vec2( ( float ) w, ( float ) h ) ) );

  std::cout << w << " " << h << std::endl;

  int x = 0;

  for( int i = 32; i < 128; i++ )
  {
    if( FT_Load_Char( face, i, FT_LOAD_RENDER ) )
      continue;

    glTexSubImage2D( GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer );

    x += g->bitmap.width;
  }

  std::shared_ptr<GUITextFont> font( new GUITextFont() );
  font->name = name;
  font->texture_atlas = texture_atlas;

  this->fonts.push_back( font );
}

std::shared_ptr<GUITextFont> GUITextManager::getFont( std::string name )
{
  for( auto f : this->fonts )
    if( f->name == name )
      return f;
}
