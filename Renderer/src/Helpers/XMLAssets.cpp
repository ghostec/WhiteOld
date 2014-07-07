#include "Renderer/Helpers/XMLAssets.h"

namespace XMLHelper
{
  void importShader( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    std::shared_ptr<Shader> shader( new Shader( name ) );
    resource_manager->addShader( name, shader );
  }

  void importMesh( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* file = el->FirstChildElement( "file" )->GetText();
    std::shared_ptr<Mesh> mesh( new Mesh( file ) );
    resource_manager->addMesh( name, mesh );
  }

  void importTexture( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* file = el->FirstChildElement( "file" )->GetText();
    std::shared_ptr<Texture> texture( new Texture( file ) );
    resource_manager->addTexture( name, texture );
  }

  void importModel( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* mesh_name = el->FirstChildElement( "mesh" )->GetText();
    const char* shader_name = el->FirstChildElement( "shader" )->GetText();
    const char* texture_name = el->FirstChildElement( "texture" )->GetText();

    std::shared_ptr<Mesh> mesh = resource_manager->getMesh( mesh_name );

    std::shared_ptr<Shader> shader =
      resource_manager->getShader( shader_name );

    std::shared_ptr<Texture> texture =
      resource_manager->getTexture( texture_name );

    std::shared_ptr<Model> model( new Model( mesh ) );
    model->setTexture( texture ); model->setShader( shader );

    resource_manager->addModel( name, model );
  }

  void importAssets( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    file_name = "../assets/xml/" + file_name + ".xml";
    doc.LoadFile( file_name.c_str( ) );

    tinyxml2::XMLElement* el = doc.RootElement();

    while( el )
    {
      if( strcmp( el->Name(), "shader" ) == 0 )
        importShader( el, resource_manager );
      if( strcmp( el->Name( ), "texture" ) == 0 )
        importTexture( el, resource_manager );
      if( strcmp( el->Name( ), "mesh" ) == 0 )
        importMesh( el, resource_manager );
      if( strcmp( el->Name( ), "model" ) == 0 )
        importModel( el, resource_manager );
      el = el->NextSiblingElement();
    }
  }
}