#include "Renderer/Helpers/XMLScene.h"

namespace XMLHelper
{
  void importCamera( tinyxml2::XMLElement* el, Scene* scene )
  {
    tinyxml2::XMLElement* ell = el->FirstChildElement( "position" );
    WMath::vec3 position( ell->FloatAttribute( "x" ),
      ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );

    ell = el->FirstChildElement( "target" );
    WMath::vec3 target( ell->FloatAttribute( "x" ),
      ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );

    std::shared_ptr<Camera> camera( new Camera() );
    CameraHelper::targetCamera( &*camera, position, target );
    scene->setCamera( camera );
  }

  void importLight( tinyxml2::XMLElement* el, Scene* scene )
  {
    tinyxml2::XMLElement* ell = el->FirstChildElement( "position" );
    WMath::vec3 position( ell->FloatAttribute( "x" ),
      ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );

    ell = el->FirstChildElement( "color" );
    WMath::vec3 color( ell->FloatAttribute( "r" ),
      ell->FloatAttribute( "g" ), ell->FloatAttribute( "b" ) );

    float attenuation = el->FirstChildElement( "attenuation" )->FloatAttribute( "value" );
    float ambient_coefficient = el->FirstChildElement( "ambient_coefficient" )->FloatAttribute( "value" );

    Light light( position, color, attenuation, ambient_coefficient );
    scene->addLight( light );
  }

  void importModel( tinyxml2::XMLElement* el, Scene* scene,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    std::shared_ptr<Model> model = resource_manager->getModel( name );
    scene->addModel( model );
  }

  Scene importScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str( ) );

    Scene scene( file_name );

    tinyxml2::XMLElement* el = doc.RootElement();

    while( el )
    {
      if( strcmp( el->Name(), "model" ) == 0 )
        importModel( el, &scene, resource_manager );
      if( strcmp( el->Name(), "light" ) == 0 )
        importLight( el, &scene );
      if( strcmp( el->Name(), "camera" ) == 0 )
        importCamera( el, &scene );
      el = el->NextSiblingElement( );
    }

    return scene;
  }
}