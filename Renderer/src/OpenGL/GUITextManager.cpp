#include "..\..\include\Renderer\OpenGL\GUITextManager.h"

GUITextManager::GUITextManager()
{
  if( FT_Init_FreeType( &this->ft ) )
    std::cout << "Could not init freetype library" << std::endl;
}

std::shared_ptr<GUITextFont> GUITextManager::getGUITextFont( std::string name, float size )
{
  for( auto f : this->fonts )
    if( f->name == name )
      return f;

  std::shared_ptr<GUITextFont> font( new GUITextFont() );

  FT_Face face;

  std::string path = "../assets/fonts/" + name + ".ttf";

  if( FT_New_Face( ft, path.c_str(), 0, &face ) )
    std::cout << "Could not open font" << std::endl;

  FT_Set_Pixel_Sizes( face, 0, size );

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

  int x = 0;

  font->name = name;
  font->texture_atlas = texture_atlas;
  font->atlas_width = w;
  font->atlas_height = h;

  for( int i = 32; i < 128; i++ )
  {
    if( FT_Load_Char( face, i, FT_LOAD_RENDER ) )
      continue;

    glTexSubImage2D( GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer );

    font->c[ i ].ax = g->advance.x >> 6;
    font->c[ i ].ay = g->advance.y >> 6;

    font->c[ i ].bw = g->bitmap.width;
    font->c[ i ].bh = g->bitmap.rows;

    font->c[ i ].bl = g->bitmap_left;
    font->c[ i ].bt = g->bitmap_top;

    font->c[ i ].tx = ( float ) x / w;

    x += g->bitmap.width;
  }

  this->fonts.push_back( font );

  return font;
}

void GUITextManager::update()
{
  for( auto& o : this->gui_texts ) o->update();
}

std::shared_ptr<GUIText> GUITextManager::makeGUIText( std::string name,
  std::string font_name, float font_size, std::string text,
  std::shared_ptr<GUIElement> parent, std::shared_ptr<Viewport> viewport )
{
  std::shared_ptr<GUITextFont> font = this->getGUITextFont( font_name, font_size );
  std::shared_ptr<GUIText> gui_text( new GUIText( name, font, viewport, parent, text ) );
  this->addGUIText( gui_text );
  return gui_text;
}

void GUITextManager::addGUIText( std::shared_ptr<GUIText> gui_text )
{
  this->gui_texts.push_back( gui_text );
}

void GUITextManager::removeGUIText( std::shared_ptr<GUIText> gui_text )
{
  this->gui_texts.erase
    ( std::remove_if( this->gui_texts.begin(), this->gui_texts.end(),
    [ & ] ( std::shared_ptr<GUIText>& o )
  { if( o == gui_text ) return true; } ),
    this->gui_texts.end() );
}