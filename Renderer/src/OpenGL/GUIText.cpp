#include "Renderer/GUIText.h"

GUIText::GUIText( std::string name, std::shared_ptr<GUITextFont> font,
    std::string text )
{
  this->name = name; this->text = text; this->font = font;

  ContainableData data;
  data.mode = CONTAINABLE_MODE_FULL;
  this->gui_element.reset( new GUIElement( data ) );

  this->setText( text );
}

void GUIText::setText( std::string text )
{
  if( text == "" ) return;

  ContainableCachedData data;
  float x = data.anchor[0];
  float y = data.anchor[1];
  float sx = 2.0f / active_window->getDimensions()[0];
  float sy = 2.0f / active_window->getDimensions()[1];

  struct point {
    float x, y, s, t;
  } coords[ 6 * text.length() ];

  int n = 0;

  float atlas_width = font->atlas_width;
  float atlas_height = font->atlas_height;

  for( const char *p = text.c_str(); *p; p++ )
  {
    float x2 =  x + font->c[*p].bl * sx;
    float y2 = -y - font->c[*p].bt * sy;
    float w = font->c[*p].bw * sx;
    float h = font->c[*p].bh * sy;

    /* Advance the cursor to the start of the next character */
    x += font->c[*p].ax * sx;
    y += font->c[*p].ay * sy;

    /* Skip glyphs that have no pixels */
    if(!w || !h)
      continue;

    coords[ n++ ] = ( point ) { x2, -y2, font->c[*p].tx, 0 };
    coords[ n++ ] =
      ( point ) { x2 + w, -y2,
        font->c[*p].tx + font->c[*p].bw / atlas_width, 0 };
    coords[ n++ ] =
      ( point ) { x2, -y2 - h, font->c[*p].tx, font->c[*p].bh / atlas_height };
    coords[ n++ ] =
      ( point ) { x2 + w, -y2,
        font->c[*p].tx + font->c[*p].bw / atlas_width, 0 };
    coords[ n++ ] =
      ( point ) { x2, -y2 - h,
        font->c[*p].tx, font->c[*p].bh / atlas_height };
    coords[ n++ ] =
      ( point ) { x2 + w, -y2 - h,
        font->c[*p].tx + font->c[*p].bw / atlas_width,
        font->c[*p].bh / atlas_height };
  }

  std::vector< WMath::vec3 > vertices, uvs;
  for( auto c : coords )
  {
    WMath::vec3 v, uv;
    v[0] = c.x; v[1] = c.y;
    uv[0] = c.s; uv[1] = c.t;
    vertices.push_back( v ); uvs.push_back( uv );
  }

  this->gui_element->getMesh()->setType( MESH_V2T );
  this->gui_element->getMesh()->setVertices( vertices );
  this->gui_element->getMesh()->setUVs( uvs );
  this->gui_element->getMesh()->resetVBO();

  this->gui_element->setTexture( this->font->texture_atlas );

  std::shared_ptr<Shader> shader( new Shader( "text" ) );
  this->gui_element->setShader( shader );
}
