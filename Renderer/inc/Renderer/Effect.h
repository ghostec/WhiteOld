#ifndef __RENDERER_EFFECT__
#define __RENDERER_EFFECT__

#include <chrono>
#include "Renderer/ModelInstance.h"
#include "WMath/interpolation.h"

typedef struct EffectComponent
{
  float current_value;
  float initial_value, final_value;
  float duration;
  void (*interpolation_function)( EffectComponent* effect_component,
                                  float time_elapsed );
  void (*effect_function)( ModelInstance* model_instance, float value );
} EffectComponent;

void interpolation_function(  EffectComponent* effect_component,
                              float time_elapsed );
void effect_function( ModelInstance* model_instance,
                      float value );
void effect_function2(  ModelInstance* model_instance,
                        float value );

EffectComponent fadeOut( float duration );

class Effect
{
  private:
    std::chrono::high_resolution_clock::time_point created_at;
    ModelInstance* model_instance;
    std::vector< EffectComponent > effect_components;
  public:
    Effect( ModelInstance* model_instance );
    void addComponent( EffectComponent effect_component );
    void execute();
};

#endif
