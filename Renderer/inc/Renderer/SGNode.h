#ifndef __WHITE_SGNODE__
#define __WHITE_SGNODE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Model.h"
#include "WMath/WMath.h"

class SGNode
{
  private:
    WMath::vec3 translate, scale;
    WMath::quaternion rotate;
    std::shared_ptr<Model> model;
    std::vector< std::shared_ptr<SGNode> > children;
    std::string name;
  public:
    SGNode( std::string name, std::shared_ptr<Model> model );
    void addChild( std::shared_ptr<SGNode> child );
    void removeChild( std::string name );
    //getters
    WMath::vec3 getTranslate() { return this->translate; }
    WMath::vec3 getScale() { return this->scale; }
    WMath::quaternion getRotate() { return this->rotate; }
    std::string getName() { return this->name; }
    std::shared_ptr<Model> getModel() { return this->model; }
    std::vector< std::shared_ptr<SGNode> > getChildren()
      { return this->children; }
    //setters
    void setTranslate( WMath::vec3 t ) { this->translate = t; }
    void setScale( WMath::vec3 s ) { this->scale = s; }
    void setRotate( WMath::quaternion r ) { this->rotate = r; }
    void setModel( std::shared_ptr<Model> model );
};

#endif
