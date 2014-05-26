#include "Renderer/Effect.h"

Effect::Effect( ModelInstance* model_instance, float duration, float initial_value, float final_value )
{
  this->initial_value = initial_value;
  this->final_value = final_value;
  this->duration = duration;
  this->model_instance = model_instance;
  this->created_at = std::chrono::high_resolution_clock::now();
}

void Effect::execute()
{
  auto t0 = std::chrono::high_resolution_clock::now();
  elapsed = std::chrono::duration_cast< std::chrono::milliseconds >
            ( t0 - created_at ).count() / 1000.0f;
  this->model_instance->setOpacity( ( ( this->final_value - this->initial_value ) / this->duration ) * elapsed + this->initial_value );
}