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

    SGNodeWorldTransform world_transform;

    std::shared_ptr<SGNode> sg_node( new SGNode( name, model ) );
    tinyxml2::XMLElement* ell = el->FirstChildElement( "position" );
    if( ell )
    {
      WMath::vec3 position( ell->FloatAttribute( "x" ),
        ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );
      world_transform.position = position;
    }

    ell = el->FirstChildElement( "scale" );
    if( ell )
    {
      WMath::vec3 scale( ell->FloatAttribute( "x" ),
        ell->FloatAttribute( "y" ), ell->FloatAttribute( "z" ) );
      world_transform.scale = scale;
    }

    sg_node->setWorldTransform( world_transform );

    scene_graph->addSGNode( sg_node );
  }

  Scene importScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str( ) );

    Scene scene( file_name );
    std::shared_ptr<SceneGraph> scene_graph( new SceneGraph() );
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

  void exportScene( std::string file_name, Scene* scene )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";

    std::queue< std::pair< std::shared_ptr<SGNode>, std::string > > bfs_q;
    std::vector< std::shared_ptr<SGNode> > bfs_v;

    std::pair< std::shared_ptr<SGNode>, std::string > root;
    root.first = scene->getSceneGraph()->getRootSGNode();
    root.second = "";

    bfs_q.push( root );
    bfs_v.push_back( scene->getSceneGraph()->getRootSGNode() );

    while( !bfs_q.empty() )
    {
      std::pair< std::shared_ptr<SGNode>, std::string > p = bfs_q.front();
      std::shared_ptr<SGNode> n = p.first;
      std::string parent = p.second;
      bfs_q.pop();

      if( n->getModel() )
      {
        tinyxml2::XMLElement* el = doc.NewElement( "sg_node" );
        tinyxml2::XMLElement* el_name = doc.NewElement( "name" );
        tinyxml2::XMLElement* el_model = doc.NewElement( "model" );
        tinyxml2::XMLElement* el_position = doc.NewElement( "position" );

        tinyxml2::XMLText* name_text = doc.NewText( n->getName().c_str() );
        tinyxml2::XMLText* model_text = doc.NewText( n->getModel()->getName().c_str() );

        SGNodeWorldTransform world_transform = n->getWorldTransform();

        WMath::vec3 p = world_transform.position;
        el_position->SetAttribute( "x", std::to_string( p[0] ).c_str() );
        el_position->SetAttribute( "y", std::to_string( p[1] ).c_str() );
        el_position->SetAttribute( "z", std::to_string( p[2] ).c_str() );

        el_name->InsertEndChild( name_text );
        el_model->InsertEndChild( model_text );
        el->InsertEndChild( el_name );
        el->InsertEndChild( el_model );
        el->InsertEndChild( el_position );

        if( parent != "root" )
        {
          tinyxml2::XMLElement* el_parent = doc.NewElement( "parent" );
          tinyxml2::XMLText* parent_text = doc.NewText( parent.c_str() );
          el_parent->InsertEndChild( parent_text );
          el->InsertEndChild( el_parent );
        }

        doc.InsertEndChild( el );
      }

      for( auto c : n->getChildren() )
      {
        if( std::find( bfs_v.begin(), bfs_v.end(), c ) == bfs_v.end() )
        {
          std::pair< std::shared_ptr<SGNode>, std::string > pair;
          pair.first = c; pair.second = n->getName();
          bfs_q.push( pair ); bfs_v.push_back( c );
        }
      }
    }

    doc.SaveFile( file_name.c_str() );
  }
}
