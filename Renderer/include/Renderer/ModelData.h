#ifndef __RENDERER_MODELDATA__
#define __RENDERER_MODELDATA__

#include <string>
#include <vector>
#include <utility>
#include "Renderer/DataHolder.h"
#include "WMath/WMath.h"

class ModelData
{
  private:
    struct DataHolders : DataHolder< WMath::vec3 >,
      DataHolder< WMath::vec4 >,
      DataHolder< float > {};
    DataHolders tables;
  public:
    template< typename T >
    T& get( std::string name );
    template< typename T >
    std::vector< std::pair< std::string, T > >& get();
    template< typename T >
    void set( std::string name, T value );
};

template<typename T>
inline T & ModelData::get( std::string name )
{
  DataHolder<T>& o = this->tables;
  return o.get( name );
}

template<typename T>
inline std::vector< std::pair< std::string, T > >& ModelData::get()
{
  DataHolder<T>& o = this->tables;
  return o.get();
}

template<typename T>
inline void ModelData::set( std::string name, T value )
{
  DataHolder<T>& o = this->tables;
  return o.set( name, value );
}

#endif