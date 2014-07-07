#include "Renderer/Helpers/XMLGUIScene.h"

namespace XMLHelper
{
  void importGUIElement( tinyxml2::XMLElement* el, GUIManager* gui_manager,
    std::string gui_scene_name )
  {

    std::string name = el->FirstChildElement( "name" )->GetText();

    if( el->FirstChildElement( "parent_name" ) )
    {
      std::string parent_name =
        el->FirstChildElement( "parent_name" )->GetText();
      gui_manager->createGUIElement( name, gui_scene_name, parent_name );
    }
    else
    {
      gui_manager->createGUIElement( name, gui_scene_name );
    }

    std::shared_ptr<ResourceManager> resource_manager =
      gui_manager->getResourceManager();

    std::shared_ptr<GUIElement> gui_el = gui_manager->getGUIElement( name );

    tinyxml2::XMLElement* state_el = el->FirstChildElement( "state" );

    while( state_el )
    {
      std::string state_name =
        state_el->FirstChildElement( "name" )->GetText();

      std::string shader_name =
        state_el->FirstChildElement( "shader" )->GetText();
      std::shared_ptr<Shader> shader =
        resource_manager->getShader( shader_name );
      std::string texture_name =
        state_el->FirstChildElement( "texture" )->GetText();
      std::shared_ptr<Texture> texture =
        resource_manager->getTexture( texture_name );

      GUIState gui_state = { shader, texture };
      gui_el->setState( state_name, gui_state );

      state_el = el->NextSiblingElement( "state" );
    }

    std::string current_state =
      el->FirstChildElement( "current_state" )->GetText();

    gui_el->setState( current_state );  
  }

  void importGUIScene( std::string file_name, GUIManager* gui_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str() );

    std::shared_ptr<ResourceManager> resource_manager =
      gui_manager->getResourceManager();

    std::string name = doc.FirstChildElement( "name" )->GetText();
    gui_manager->createGUIScene( name );

    tinyxml2::XMLElement* gui_el = doc.FirstChildElement( "gui_element" );

    while( gui_el )
    {
      importGUIElement( gui_el, gui_manager, name );
      gui_el = gui_el->NextSiblingElement( "gui_element" );
    }
  }
}