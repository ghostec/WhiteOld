#include "Physics/Helpers/XMLPhysics.h"

namespace XMLHelper
{
  void createBody( tinyxml2::XMLElement* el,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<PhysicsManager> physics_manager )
  {
    const char* sg_node_name = el->FirstChildElement( "sg_node" )->GetText();
    std::shared_ptr<SGNode> sg_node = scene_graph->getNode( sg_node_name );

    std::shared_ptr<Body> body;

    if( strcmp( sg_node_name, "plane" ) != 0 ) body.reset( new Body( sg_node ) );
    else
    {
      body.reset( new Body( sg_node, true ) );
    }

    physics_manager->addBody( body );
  }

  void importPhysics( std::string file_name,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<PhysicsManager> physics_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str( ) );

    tinyxml2::XMLElement* el = doc.RootElement();

    while( el )
    {
      if( strcmp( el->Name(), "body" ) == 0 )
        createBody( el, scene_graph, physics_manager );
      el = el->NextSiblingElement( );
    }
  }
}