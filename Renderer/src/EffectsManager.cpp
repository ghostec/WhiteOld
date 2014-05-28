#include "Renderer/EffectsManager.h"

void EffectsManager::addEffect( Effect effect )
{
  this->effects.push_back( effect );
}

void EffectsManager::execute()
{
  std::vector< int > marked_indices;
  for( int i=0; i < this->effects.size(); i++ )
  {
    if( this->effects[i].getEffectComponentsSize() == 0 )
    {
      marked_indices.push_back( i );
    }
    else
    {
      this->effects[i].execute( );
    }
  }

  std::sort(  marked_indices.begin( ), marked_indices.end( ),
              std::greater<int>( ) );

  remove_marked_indices( &this->effects, &marked_indices );
}