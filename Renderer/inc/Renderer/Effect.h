#ifndef __RENDERER_EFFECT__
#define __RENDERER_EFFECT__

#include <chrono>
#include "Renderer/ModelInstance.h"

class Effect
{
  private:
    float duration;
    float elapsed = 0.0f;
    float initial_value, final_value;
    std::chrono::high_resolution_clock::time_point created_at;
    ModelInstance* model_instance;
  public:
    Effect( ModelInstance* model_instance, float duration,
            float initial_value, float final_value );
    void execute();
};

#endif
