#include "Renderer/EffectsManager.h"

bool isIndexMarked( std::vector< int >& marked, int& i )
{
  for( int index : marked )
  {
    if( index == i )
    {
      i++;
      return true;
    }
  }
  i++;
  return false;
}

void EffectsManager::addEffect( Effect effect )
{
  this->effects.push_back( effect );
}

void EffectsManager::execute()
{
  std::vector< int > marked;
  int index = 0;
  for( Effect effect : this->effects )
  {
    if( effect.isDone() )
    {
      marked.push_back( index );
    }
    else
    {
      effect.execute();
    }
    index += 1;
  }

  int i = 0;
  this->effects.erase( std::remove_if(  this->effects.begin(),
                                        this->effects.end(),
                                        isIndexMarked( marked, i ) ), this->effects.end() );
}