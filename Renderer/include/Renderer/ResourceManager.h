#ifndef __RENDERER_RESOURCEMANAGER__
#define __RENDERER_RESOURCEMANAGER__

#include <map>
#include <string>
#include <memory>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Renderer/ModelData.h"
#include "Renderer/ModelData.h"
#include "Renderer/GUIElement.h"
#include <typeinfo>

template<typename T>
using ResourceMap = std::map< std::string, std::shared_ptr<T> >;

class ResourceManager
{
  private:
    struct DataHolders : DataHolder< std::shared_ptr< Shader > >,
      DataHolder< std::shared_ptr< Texture > >,
      DataHolder< std::shared_ptr < Material > >,
      DataHolder< std::shared_ptr< Mesh > >,
      DataHolder< std::shared_ptr< Model > > {};
    DataHolders data_holders;
  public:
    template< typename T >
    T& get( std::string name );
    template< typename T >
    std::vector< std::pair< std::string, T > >& get();
    template< typename T >
    void set( std::string name, T value );
};

template<typename T>
inline T & ResourceManager::get( std::string name )
{
  DataHolder<T>& o = this->data_holders;
  return o.get( name );
}

template<typename T>
inline std::vector< std::pair< std::string, T > >& ResourceManager::get()
{
  DataHolder<T>& o = this->data_holders;
  return o.get();
}

template<typename T>
inline void ResourceManager::set( std::string name, T value )
{
  DataHolder<T>& o = this->data_holders;
  return o.set( name, value );
}

#endif
