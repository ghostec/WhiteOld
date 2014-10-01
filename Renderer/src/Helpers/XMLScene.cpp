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

  void createSGNode( tinyxml2::XMLElement* el,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* model_name = el->FirstChildElement( "model" )->GetText();
    std::shared_ptr<Model> model = resource_manager->getModel( model_name );

    std::shared_ptr<SGNode> sg_node( new SGNode( name, model ) );
    tinyxml2::XMLElement* ell = el->FirstChildElement( "position" );
    if( ell )
    {
      WMath::vec3 position( ell->FloatAttribute( "x" ),
        ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );
      sg_node->setTranslate( position );
    }

    ell = el->FirstChildElement( "scale" );
    if( ell )
    {
      WMath::vec3 scale( ell->FloatAttribute( "x" ),
        ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );
      sg_node->setScale( scale );
    }
    else
    {
      WMath::vec3 scale( 1.0 );
      sg_node->setScale( scale );
    }

    scene_graph->addNode( sg_node );
  }

  Scene importScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str( ) );

    Scene scene( file_name );
    std::shared_ptr<SceneGraph> scene_graph( new SceneGraph );
    scene.setSceneGraph( scene_graph );

    tinyxml2::XMLElement* el = doc.RootElement();

    while( el )
    {
      if( strcmp( el->Name( ), "sg_node" ) == 0 )
        createSGNode( el, scene_graph, resource_manager );
      else if( strcmp( el->Name(), "light" ) == 0 )
        importLight( el, &scene );
      else if( strcmp( el->Name(), "camera" ) == 0 )
        importCamera( el, &scene );
      el = el->NextSiblingElement( );
    }

    return scene;
  }
}