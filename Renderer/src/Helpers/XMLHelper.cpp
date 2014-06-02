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
    resource_manager->addShader( shader, name );
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
    resource_manager->addTexture( texture, name );
  }

  std::shared_ptr<ModelAsset> parseXMLModelAsset( tinyxml2::XMLElement* element )
  {
    
    std::shared_ptr<ModelAsset> model_asset( new ModelAsset(  parseXMLstring( element,
                                                              "file" ),
                                                              MODEL_ASSET_3D ) );
    return model_asset;
  }

  void parseXMLModelAsset( tinyxml2::XMLElement* element,
    std::shared_ptr<ResourceManager> resource_manager )
  {
    std::shared_ptr<ModelAsset> model_asset = parseXMLModelAsset( element );
    const char* texture_name = parseXMLstring( element, "texture" );
    std::shared_ptr<Texture> texture = resource_manager->getTexture( texture_name );
    model_asset->setTexture( texture );

    tinyxml2::XMLElement* shaders = element->FirstChildElement( "shaders" )->FirstChildElement();
    do
    {
      const char* shader_name = parseXMLstring( shaders, "name" );
      std::shared_ptr<Shader> shader = resource_manager->getShader( shader_name );
      model_asset->addShader( shader );
      shaders = shaders->NextSiblingElement( );
    } while( shaders );
    
    const char* name = parseXMLstring( element, "name" );
    resource_manager->addModelAsset( model_asset, name );
  }

  std::shared_ptr<ModelInstance> parseXMLModelInstance
    ( tinyxml2::XMLElement* element,
      std::shared_ptr<ResourceManager> resource_manager )
  {
    const char* name = parseXMLstring( element, "name" );
    const char* model_asset_name = parseXMLstring( element, "model_asset" );
    std::shared_ptr<ModelAsset> model_asset = resource_manager->getModelAsset( model_asset_name );
    std::shared_ptr<ModelInstance> model_instance( new ModelInstance( model_asset ) );
    resource_manager->addModelInstance( model_instance, name );
    return model_instance;
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
      else if( strcmp( element->Name( ), "model_asset" ) == 0 )
      {
        parseXMLModelAsset( element, resource_manager );
      }
      else if( strcmp( element->Name( ), "model_instance" ) == 0 )
      {
        std::shared_ptr<ModelInstance> model_instance = 
          parseXMLModelInstance( element, resource_manager );
        scene->addModel( model_instance );
      }
      element = element->NextSiblingElement();
    } while( element );

    return scene;
  }
}