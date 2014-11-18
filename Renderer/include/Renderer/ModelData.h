#ifndef __RENDERER_MODELDATA__
#define __RENDERER_MODELDATA__

#include <string>
#include <vector>
#include <utility>
#include "WMath/WMath.h"

template< typename T >
class ObjectTable
{
  private:
    std::vector< std::pair< std::string, T > > v;
  public:
    void set( std::string name, T value );
    T& get( std::string name );
    std::vector< std::pair< std::string, T > >& get();
};

class ModelData
{
  private:
    struct ObjectTables : ObjectTable< WMath::vec3 >,
      ObjectTable< WMath::vec4 >,
      ObjectTable< float > {};
    ObjectTables tables;
  public:
    template< typename T >
    T& get( std::string name );
    template< typename T >
    std::vector< std::pair< std::string, T > >& get();
    template< typename T >
    void set( std::string name, T value );
};

template<typename T>
inline void ObjectTable<T>::set( std::string name, T value )
{
  bool found = false;
  for( auto o : this->v )
  {
    if( o.first == name )
    {
      found = true;
      o.second = value;
    }
  }
  if( !found ) this->v.push_back( { name, value } );
}

template<typename T>
inline T & ObjectTable<T>::get( std::string name )
{
  for( auto& o : this->v )
  {
    if( o.first == name )
    {
      return o.second;
    }
  }
}

template<typename T>
inline std::vector< std::pair< std::string, T > >& ObjectTable<T>::get()
{
  return this->v;
}

template<typename T>
inline T & ModelData::get( std::string name )
{
  ObjectTable<T>& o = this->tables;
  return o.get( name );
}

template<typename T>
inline std::vector< std::pair< std::string, T > >& ModelData::get()
{
  ObjectTable<T>& o = this->tables;
  return o.get();
}

template<typename T>
inline void ModelData::set( std::string name, T value )
{
  ObjectTable<T>& o = this->tables;
  return o.set( name, value );
}

#endif