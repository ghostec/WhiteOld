#ifndef __WHITE_RENDERER_MATERIAL__
#define __WHITE_RENDERER_MATERIAL__

#include <memory>
#include "Renderer/Texture.h"
#include "WMath/WMath.h"

class Material
{
  private:
    std::shared_ptr<Texture> texture;
    WMath::vec4 color = WMath::vec4(1.0f);
    bool activate_texture, activate_color;
  public:
    Material();
    void use();
    void unuse();
    void activateTexture( bool v ) { this->activate_texture = v; }
    void activateColor( bool v ) { this->activate_color = v; }
    // setters
    void setTexture( std::shared_ptr<Texture> t ) { this->texture = t; }
    void setColor( WMath::vec4 color ) { this->color = color; }
    // getters
    std::shared_ptr<Texture> getTexture() { return this->texture; }
    WMath::vec4 getColor() { return this->color; }
    bool isTextureActivated() { return this->activate_texture; }
    bool isColorActivated() { return this->activate_color; }
};

#endif