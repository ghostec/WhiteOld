#include "Renderer/Effect.h"

void interpolation_function(  EffectComponent* effect_component,
                              float time_elapsed )
{
  effect_component->current_value =
    WMath::linear_interpolation(  time_elapsed, effect_component->duration,
                                  effect_component->initial_value, 
                                  effect_component->final_value );
}

void effect_function( ModelInstance* model_instance,
                      float value )
{
  model_instance->setOpacity( value );
}

void effect_function2(  ModelInstance* model_instance,
                        float value )
{
  WMath::translate( model_instance->getTransform(), WMath::vec3( 0.005f, 0.0f, 0.0f ) );
}

EffectComponent fadeOut( float duration )
{
  EffectComponent effect_component;
  effect_component.duration = duration;
  effect_component.interpolation_function = &interpolation_function;
  effect_component.effect_function = &effect_function;
  effect_component.initial_value = 1.0f;
  effect_component.final_value = 0.0f;
  return effect_component;
}

Effect::Effect( ModelInstance* model_instance )
{
  this->model_instance = model_instance;
  this->created_at = std::chrono::high_resolution_clock::now();
  this->done = false;
}

void Effect::execute()
{
  auto t0 = std::chrono::high_resolution_clock::now( );
  float elapsed = std::chrono::duration_cast< std::chrono::milliseconds >
                  ( t0 - this->created_at ).count( ) / 1000.0f;
  this->done = true;
  for( EffectComponentPair ecp : this->effect_components )
  {
    EffectComponent* effect_component = &ecp.first;
    bool* done = &ecp.second;
    if( *done == true ) continue;
    if( elapsed > effect_component->duration )
    {
      ( effect_component->effect_function )(  this->model_instance,
                                              effect_component->final_value );
      *done = true;
    }
    else
    {
      ( effect_component->interpolation_function )( effect_component, elapsed );
      ( effect_component->effect_function )(  this->model_instance,
                                              effect_component->current_value );
      this->done = false;
    }
  }
}

void Effect::addComponent( EffectComponent effect_component )
{
  this->effect_components.push_back( std::make_pair(  effect_component,
                                                      false ) );
}