#include "Renderer/Helpers/XMLAssets.h"

namespace XMLHelper
{
  void importShader( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    std::shared_ptr<Shader> shader( new Shader( name ) );
    resource_manager->set< std::shared_ptr< Shader > >( name, shader );
  }

  void importMesh( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* file = el->FirstChildElement( "file" )->GetText();
    std::shared_ptr<Mesh> mesh( new Mesh( file ) );
    resource_manager->set< std::shared_ptr< Mesh > >( name, mesh );
  }

  void importTexture( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* file = el->FirstChildElement( "file" )->GetText();
    std::shared_ptr<Texture> texture( new Texture( file ) );
    resource_manager->set< std::shared_ptr< Texture > >( name, texture );
  }

  void importMaterial( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText();
    const char* texture_name = el->FirstChildElement( "texture" )->GetText();
    std::shared_ptr<Texture> texture =
      resource_manager->get< std::shared_ptr<Texture> >( texture_name );
    std::shared_ptr<Material> material( new Material() );
    material->setTexture( texture );
    resource_manager->set< std::shared_ptr< Material > >( name, material );
  }

  void importModel( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = el->FirstChildElement( "name" )->GetText(); 
    
    const char* mesh_name = el->FirstChildElement( "mesh" )->GetText( );
    std::shared_ptr<Mesh> mesh =
      resource_manager->get< std::shared_ptr< Mesh > >( mesh_name );
    std::shared_ptr<Model> model( new Model( name, mesh ) );

    const char* shader_name = el->FirstChildElement( "shader" )->GetText();
    std::shared_ptr<Shader> shader =
      resource_manager->get< std::shared_ptr< Shader > >( shader_name );
    model->setShader( shader );

    if( el->FirstChildElement( "material" ) )
    {
      const char* material_name = el->FirstChildElement( "material" )->GetText();
      model->setMaterial( resource_manager->get< std::shared_ptr< Material > >( material_name ) );
    }

    resource_manager->set< std::shared_ptr< Model > >( name, model );
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
      if( strcmp( el->Name(), "texture" ) == 0 )
        importTexture( el, resource_manager );
      if( strcmp( el->Name(), "material" ) == 0 )
        importMaterial( el, resource_manager );
      if( strcmp( el->Name(), "mesh" ) == 0 )
        importMesh( el, resource_manager );
      if( strcmp( el->Name(), "model" ) == 0 )
        importModel( el, resource_manager );
      el = el->NextSiblingElement();
    }
  }
}