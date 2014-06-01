#include "Renderer/Helpers/XMLHelper.h"

namespace XMLHelper
{
  void parseXML( )
  {
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "../assets/xml/example.xml" );
    std::cout << doc.FirstChildElement( )->FirstChildElement( )->FirstChildElement( )->GetText( ) << std::endl;
  }
}