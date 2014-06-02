#ifndef __RENDERER_EFFECT__
#define __RENDERER_EFFECT__

#include <chrono>
#include <memory>
#include <utility>
#include <functional>
#include "Renderer/ModelInstance.h"
#include "WMath/interpolation.h"

template<typename Class>
void remove_marked_indices( std::shared_ptr< std::vector< Class > > v, 
  std::shared_ptr< std::vector< int > > marked_indices )
{
  std::sort(  marked_indices->begin( ), marked_indices->end( ),
              std::greater<int>( ) );
  for( int i : *marked_indices )
    v->erase( std::next( v->begin(), i ) );
}

typedef struct EffectComponent
{
  float current_value;
  float initial_value, final_value;
  float duration;
  void (*interpolation_function)
    ( std::shared_ptr< EffectComponent > effect_component,
      float time_elapsed );
  void (*effect_function)
    ( std::shared_ptr< ModelInstance > model_instance, float value );
} EffectComponent;

void interpolation_function
  ( std::shared_ptr< EffectComponent > effect_component,
    float time_elapsed );
void effect_function( std::shared_ptr<ModelInstance> model_instance,
  float value );
void effect_function2( std::shared_ptr<ModelInstance> model_instance,
  float value );
void effect_function3( std::shared_ptr<ModelInstance> model_instance,
  float value );

EffectComponent fadeOut( float duration );

class Effect
{
  private:
    std::chrono::high_resolution_clock::time_point created_at;
    std::shared_ptr<ModelInstance> model_instance;
    std::vector< EffectComponent > effect_components;
  public:
    Effect( std::shared_ptr<ModelInstance> model_instance );
    void addComponent( EffectComponent effect_component );
    void execute();
    // getters
    int getEffectComponentsSize() { return this->effect_components.size(); };
};

#endif
