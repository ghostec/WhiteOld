#include "Renderer/Helpers/XMLHelper.h"

namespace XMLHelper
{
  const char* parseXMLstring( tinyxml2::XMLElement* element, const char* name )
  {
    return element->FirstChildElement( name )->GetText();
  }

  WMath::vec3 parseXMLvec3( tinyxml2::XMLElement* element, const char* name )
  {
    float x = element->FirstChildElement( name )->FloatAttribute( "x" );
    float y = element->FirstChildElement( name )->FloatAttribute( "y" );
    float z = element->FirstChildElement( name )->FloatAttribute( "z" );
    return WMath::vec3( x, y, z );
  }
  
  std::shared_ptr<Camera> parseXMLCamera( tinyxml2::XMLElement* element )
  {
    WMath::vec3 position  = parseXMLvec3( element, "position" );
    WMath::vec3 target    = parseXMLvec3( element, "target" );
    std::shared_ptr<Camera> camera( new Camera( position, target ) );
    return camera;
  }

  std::shared_ptr<Shader> parseXMLShader( tinyxml2::XMLElement* element )
  {
    std::shared_ptr<Shader> shader( new Shader( parseXMLstring( element,
                                                                "name" ) ) );
    return shader;
  }

  void parseXMLShader( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Shader> shader = parseXMLShader( element );
    const char* name = parseXMLstring( element, "name" );
    resource_manager->addShader( name, shader );
  }

  std::shared_ptr<Texture> parseXMLTexture( tinyxml2::XMLElement* element )
  {
    std::shared_ptr<Texture> texture( new Texture( parseXMLstring( element,
                                      "file" ) ) );
    return texture;
  }

  void parseXMLTexture( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Texture> texture = parseXMLTexture( element );
    const char* name = parseXMLstring( element, "name" );
    resource_manager->addTexture( name, texture );
  }

  std::shared_ptr<Mesh> parseXMLMesh( tinyxml2::XMLElement* element )
  {
    
    std::shared_ptr<Mesh> mesh( new Mesh(  parseXMLstring( element,
      "file" ) ) );
    return mesh;
  }

  void parseXMLMesh( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Mesh> mesh = parseXMLMesh( element );
    const char* name = parseXMLstring( element, "name" );

    resource_manager->addMesh( name, mesh );
  }

  std::shared_ptr<Model> parseXMLModel
    ( tinyxml2::XMLElement* element,
      std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = parseXMLstring( element, "name" );
    const char* mesh_name = parseXMLstring( element, "mesh" );
    std::shared_ptr<Mesh> mesh = resource_manager->getMesh( mesh_name );
    std::shared_ptr<Model> model( new Model( mesh ) );
    const char* shader_name = parseXMLstring( element, "shader" );
    std::shared_ptr<Shader> shader = resource_manager->getShader( shader_name );
    model->setShader( shader );
    const char* texture_name = parseXMLstring( element, "texture" );
    std::shared_ptr<Texture> texture =
      resource_manager->getTexture( texture_name );
    model->setTexture( texture );

    resource_manager->addModel( name, model );
    return model;
  }

  std::shared_ptr<Scene> parseXMLScene
    ( std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "../assets/xml/example.xml" );

    std::shared_ptr<Scene> scene( new Scene() );

    tinyxml2::XMLElement* element = doc.FirstChildElement( "scene" )->FirstChildElement();
    do
    {
      if( strcmp( element->Name(), "camera" ) == 0 )
      {
        std::shared_ptr<Camera> camera = parseXMLCamera( element );
        scene->setCamera( camera ); 
      }
      else if( strcmp( element->Name( ), "shader" ) == 0 )
      {
        parseXMLShader( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "texture" ) == 0 )
      {
        parseXMLTexture( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "mesh" ) == 0 )
      {
        parseXMLMesh( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "model" ) == 0 )
      {
        std::shared_ptr<Model> model = 
          parseXMLModel( element, resource_manager );
        scene->addModel( model );
      }
      element = element->NextSiblingElement();
    } while( element );

    return scene;
  }
}