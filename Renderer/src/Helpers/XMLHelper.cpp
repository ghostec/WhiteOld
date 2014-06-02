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

  std::shared_ptr<Texture> parseXMLTexture( tinyxml2::XMLElement* element )
  {
    std::shared_ptr<Texture> texture( new Texture( parseXMLstring( element,
                                      "file" ) ) );
    return texture;
  }

  std::shared_ptr<ModelAsset> parseXMLModelAsset( tinyxml2::XMLElement* element )
  {
    
    std::shared_ptr<ModelAsset> model_asset( new ModelAsset(  parseXMLstring( element,
                                                              "file" ),
                                                              MODEL_ASSET_3D ) );
    return model_asset;
  }

  std::shared_ptr<Scene> parseXMLScene( ResourceManager* resource_manager )
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
        scene->setCamera( camera.get() ); 
      }
      else if( strcmp( element->Name( ), "shader" ) == 0 )
      {
        std::shared_ptr<Shader> shader = parseXMLShader( element );
        const char* name = parseXMLstring( element, "name" );
        resource_manager->addShader( shader, name );
      }
      else if( strcmp( element->Name( ), "texture" ) == 0 )
      {
        std::shared_ptr<Texture> texture = parseXMLTexture( element );
        const char* name = parseXMLstring( element, "name" );
        resource_manager->addTexture( texture, name );
      }
      else if( strcmp( element->Name( ), "model_asset" ) == 0 )
      {
        std::shared_ptr<ModelAsset> model_asset = parseXMLModelAsset( element );
        const char* name = parseXMLstring( element, "name" );
        const char* texture_name = parseXMLstring( element, "texture" );
        std::shared_ptr<Texture> texture = resource_manager->getTexture( texture_name );
        model_asset->setTexture( texture.get() );
        const char* shader_name = parseXMLstring( element, "shader" );
        std::shared_ptr<Shader> shader = resource_manager->getShader( shader_name );
        model_asset->addShader( shader.get( ) );
        resource_manager->addModelAsset( model_asset, name );
      }
      else if( strcmp( element->Name( ), "model_instance" ) == 0 )
      {
        const char* name = parseXMLstring( element, "name" );
        const char* model_asset_name = parseXMLstring( element, "model_asset" );
        std::shared_ptr<ModelAsset> model_asset = resource_manager->getModelAsset( model_asset_name );
        std::shared_ptr<ModelInstance> model_instance( new ModelInstance( model_asset.get() ) );
        resource_manager->addModelInstance( model_instance, name );
        scene->addModel( model_instance.get() );
      }
      element = element->NextSiblingElement();
    } while( element );

    return scene;
  }
}