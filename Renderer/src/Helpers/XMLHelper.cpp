#include "Renderer/Helpers/XMLHelper.h"

namespace XMLHelper
{
  const char* parseString( tinyxml2::XMLElement* element, const char* name )
  {
    return element->FirstChildElement( name )->GetText();
  }

  WMath::vec3 parseVec3( tinyxml2::XMLElement* element, const char* name )
  {
    float x = element->FirstChildElement( name )->FloatAttribute( "x" );
    float y = element->FirstChildElement( name )->FloatAttribute( "y" );
    float z = element->FirstChildElement( name )->FloatAttribute( "z" );
    return WMath::vec3( x, y, z );
  }
  
  std::shared_ptr<Camera> parseCamera( tinyxml2::XMLElement* element )
  {
    WMath::vec3 position  = parseVec3( element, "position" );
    WMath::vec3 target    = parseVec3( element, "target" );
    std::shared_ptr<Camera> camera( new Camera( position, target ) );
    return camera;
  }

  std::shared_ptr<Shader> parseShader( tinyxml2::XMLElement* element )
  {
    std::shared_ptr<Shader> shader( new Shader( parseString( element,
                                                                "name" ) ) );
    return shader;
  }

  void parseShader( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Shader> shader = parseShader( element );
    const char* name = parseString( element, "name" );
    resource_manager->addShader( name, shader );
  }

  std::shared_ptr<Texture> parseTexture( tinyxml2::XMLElement* element )
  {
    std::shared_ptr<Texture> texture( new Texture( parseString( element,
                                      "file" ) ) );
    return texture;
  }

  void parseTexture( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Texture> texture = parseTexture( element );
    const char* name = parseString( element, "name" );
    resource_manager->addTexture( name, texture );
  }

  std::shared_ptr<Mesh> parseMesh( tinyxml2::XMLElement* element )
  {
    
    std::shared_ptr<Mesh> mesh( new Mesh(  parseString( element,
      "file" ) ) );
    return mesh;
  }

  void parseMesh( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<Mesh> mesh = parseMesh( element );
    const char* name = parseString( element, "name" );

    resource_manager->addMesh( name, mesh );
  }

  std::shared_ptr<Model> parseModel
    ( tinyxml2::XMLElement* element,
      std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = parseString( element, "name" );
    const char* mesh_name = parseString( element, "mesh" );
    std::shared_ptr<Mesh> mesh = resource_manager->getMesh( mesh_name );
    std::shared_ptr<Model> model( new Model( mesh ) );
    const char* shader_name = parseString( element, "shader" );
    std::shared_ptr<Shader> shader = resource_manager->getShader( shader_name );
    model->setShader( shader );
    const char* texture_name = parseString( element, "texture" );
    std::shared_ptr<Texture> texture =
      resource_manager->getTexture( texture_name );
    model->setTexture( texture );

    resource_manager->addModel( name, model );
    return model;
  }

Scene loadScene( std::string file_name,
  std::shared_ptr<ResourceManager> resource_manager )
  {
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "../assets/xml/example.xml" );

    Scene scene;

    tinyxml2::XMLElement* element = doc.FirstChildElement( "scene" )->FirstChildElement();
    do
    {
      if( strcmp( element->Name(), "camera" ) == 0 )
      {
        std::shared_ptr<Camera> camera = parseCamera( element );
        scene.setCamera( camera ); 
      }
      else if( strcmp( element->Name( ), "shader" ) == 0 )
      {
        parseShader( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "texture" ) == 0 )
      {
        parseTexture( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "mesh" ) == 0 )
      {
        parseMesh( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "model" ) == 0 )
      {
        std::shared_ptr<Model> model = 
          parseModel( element, resource_manager );
        scene.addModel( model );
      }
      element = element->NextSiblingElement();
    } while( element );

    return scene;
  }
}