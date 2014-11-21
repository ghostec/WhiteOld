#ifndef __WHITE_RENDERER_DATAHOLDER__
#define __WHITE_RENDERER_DATAHOLDER__

#include <string>
#include <vector>
#include <utility>

template< typename T >
class DataHolder
{
private:
  std::vector< std::pair< std::string, T > > v;
public:
  void set( std::string name, T value );
  T& get( std::string name );
  std::vector< std::pair< std::string, T > >& get();
};

template<typename T>
inline void DataHolder<T>::set( std::string name, T value )
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
inline T & DataHolder<T>::get( std::string name )
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
inline std::vector< std::pair< std::string, T > >& DataHolder<T>::get()
{
  return this->v;
}

#endif