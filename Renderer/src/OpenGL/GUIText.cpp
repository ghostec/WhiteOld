#include "Renderer/GUIText.h"

GUIText::GUIText( std::string name, std::shared_ptr<GUITextFont> font,
  std::shared_ptr<Viewport> viewport, std::shared_ptr<GUIElement> parent,
  std::string text )
{
  this->name = name;
  this->font = font;
  this->text = text;
  this->viewport = viewport;
  this->parent = parent;

  ContainableData data;
  data.mode = CONTAINABLE_MODE_BOX;
  data.mode_data.box.anchor_mode = CONTAINABLE_ANCHOR_MODE_ABSOLUTE;
  data.mode_data.box.dimensions_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;

  this->gui_element.reset( new GUIElement( name, data ) );
  this->gui_element->getMesh()->setType( MESH_V2T );
  this->gui_element->setTexture( font->texture_atlas );

  std::shared_ptr<Shader> shader( new Shader( "text" ) );
  this->gui_element->setShader( shader );

  this->setText( text );
}

void GUIText::setText( std::string text )
{
  if( text == "" ) return;

  this->text = text;

  this->updateGUIElement();
}

void GUIText::update()
{
  this->updateGUIElement();
}

void GUIText::hide()
{

}

void GUIText::show()
{

}

void GUIText::updateGUIElement()
{
  ContainableCachedData viewport_data =
    this->viewport->getContainableCachedData();

  if( cached_viewport_dimensions[ 0 ] != viewport_data.dimensions[ 0 ] &&
    cached_viewport_dimensions[ 1 ] != viewport_data.dimensions[ 1 ] )
  {
    this->cached_viewport_dimensions = viewport_data.dimensions;

    std::vector< WMath::vec3 > vertices, uvs;
    vertices.reserve( 6 * text.length() );
    uvs.reserve( 6 * text.length() );

    float text_width = 0.0f, text_height = 0.0f;
    for( const char *p = text.c_str(); *p; p++ )
    {
      text_height = std::max( text_height, this->font->c[ *p ].bh );
      text_width += this->font->c[ *p ].bw;
    }

    std::cout << text_height << " " << text_width << std::endl;

    float x = 0, y = 0, sx, sy;

    sx = 2.0f / text_width;
    sy = 2.0f / text_height;

    //sx = sy = 1.0f;

    for( const char *p = text.c_str(); *p; p++ )
    {
      float x2 = x + this->font->c[ *p ].bl * sx;
      float y2 = -y - this->font->c[ *p ].bt * sy;
      float w = this->font->c[ *p ].bw * sx;
      float h = this->font->c[ *p ].bh * sy;

      /* Advance the cursor to the start of the next character */
      x += this->font->c[ *p ].ax * sx;
      y += this->font->c[ *p ].ay * sy;

      /* Skip glyphs that have no pixels */
      if( !w || !h )
        continue;

      vertices.push_back( WMath::vec3( x2, -y2, 0 ) );      
      vertices.push_back( WMath::vec3( x2 + w, -y2, 0 ) ); 
      vertices.push_back( WMath::vec3( x2, -y2 - h, 0 ) );
      vertices.push_back( WMath::vec3( x2 + w, -y2, 0 ) );
      vertices.push_back( WMath::vec3( x2, -y2 - h, 0 ) );
      vertices.push_back( WMath::vec3( x2 + w, -y2 - h, 0 ) );

      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx, 0, 0 ) );
      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx +
        this->font->c[ *p ].bw / this->font->atlas_width, 0, 0 ) );
      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx,
        this->font->c[ *p ].bh / this->font->atlas_height, 0 ) );
      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx +
        this->font->c[ *p ].bw / this->font->atlas_width, 0, 0 ) );
      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx,
        this->font->c[ *p ].bh / this->font->atlas_height, 0 ) );
      uvs.push_back( WMath::vec3( this->font->c[ *p ].tx +
        this->font->c[ *p ].bw / this->font->atlas_width,
        this->font->c[ *p ].bh / this->font->atlas_height, 0 ) );
    }

    ContainableData data;
    data.mode = CONTAINABLE_MODE_BOX;
    data.mode_data.box.anchor_mode = CONTAINABLE_ANCHOR_MODE_ABSOLUTE;
    data.mode_data.box.anchor_position = CONTAINABLE_ANCHOR_TOP_LEFT;
    data.mode_data.box.anchor_x = - text_width / 2.0f;
    data.mode_data.box.anchor_y = text_height/ 2.0f;
    data.mode_data.box.dimensions_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
    data.mode_data.box.smaller_dimension = text_height;
    data.mode_data.box.aspect_ratio = text_width / text_height;

    this->gui_element->setContainableData( data );

    this->gui_element->getMesh()->setVertices( vertices );
    this->gui_element->getMesh()->setUVs( uvs );
    this->gui_element->getMesh()->resetVBO();
  }
}

void GUIText::setFont( std::shared_ptr<GUITextFont> font )
{
}
