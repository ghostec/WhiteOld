#include "Renderer/Material.h"

Material::Material()
{
  this->activate_color = true;
  this->activate_texture = true;
}

void Material::use()
{
  if( this->texture ) this->texture->use();
}

void Material::unuse()
{
  if( this->texture ) this->texture->unuse();
} 