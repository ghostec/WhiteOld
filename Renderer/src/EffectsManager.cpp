#include "Renderer/EffectsManager.h"

void EffectsManager::addEffect( Effect* effect )
{
  this->effects.push_back( effect );
}