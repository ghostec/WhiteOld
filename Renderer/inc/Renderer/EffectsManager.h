#ifndef __RENDERER_EFFECTSMANAGER__
#define __RENDERER_EFFECTSMANAGER__

#include <vector>
#include "Renderer/Effect.h"

class EffectsManager
{
  private:
    std::vector< Effect* > effects;
  public:
    void addEffect( Effect* effect );
};

#endif