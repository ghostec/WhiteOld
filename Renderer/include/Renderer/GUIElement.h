#ifndef __WHITE_RENDERER_GUIELEMENT__
#define __WHITE_RENDERER_GUIELEMENT__

#include <memory>
#include "Renderer/Containable.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/SGNode.h"

typedef enum GUIType
{
  DRAWNABLE, CONTAINER
} GUIType;

class GUIElement : public Containable<GUIElement>
{
  private:
    std::shared_ptr<Model> model;
    std::shared_ptr<SGNode> sg_node;
  public:
    GUIElement( ContainableData data );
    // setters
    void setShader( std::shared_ptr<Shader> shader );
    void setTexture( std::shared_ptr<Texture> texture );
    using Containable<GUIElement>::setLeftChild;
    void setLeftChild( std::shared_ptr<GUIElement> child );
    // getters
    std::shared_ptr<SGNode> getSGNode() { return this->sg_node; }
    std::shared_ptr<Mesh> getMesh() { return this->model->getMesh(); }
    std::shared_ptr<Texture> getTexture() { return this->model->getTexture(); }
};

#endif
