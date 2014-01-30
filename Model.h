#ifndef __WHITE_MODEL__
#define __WHITE_MODEL__

#include <iostream>
#include "Math.h"

class Model
{
  public:
    virtual void draw() = 0;
    virtual void translate( Vector3 vector ) = 0;
    virtual void scale( Vector3 vector ) = 0;
    virtual void rotate( float degrees, Vector3 vector ) = 0;
};

class ModelOpenGL : public Model
{
  private:
  public:
    void draw();
    void translate( Vector3 vector );
    void scale( Vector3 vector );
    void rotate( float degrees, Vector3 vector );
};

void ModelOpenGL::draw()
{
  std::cout << "Placeholder ModelOpenGL::draw()" << std::endl;
}

void ModelOpenGL::translate( Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::translate()" << std::endl;
}

void ModelOpenGL::scale( Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::scale()" << std::endl;
}

void ModelOpenGL::rotate( float degrees, Vector3 vector )
{
  std::cout << "Placeholder ModelOpenGL::rotate()" << std::endl;
}

#endif
