#ifndef __WHITE_MODEL__
#define __WHITE_MODEL__

#include <iostream>
#include <string>
#include "Math.h"
#include "ModelHelper.h"

typedef enum _ModelFileType { OBJ } ModelFileType;

class Model
{
  public:
    virtual void draw() = 0;
    virtual void translate( Vector3 vector ) = 0;
    virtual void scale( Vector3 vector ) = 0;
    virtual void rotate( float degrees, Vector3 vector ) = 0;
};

#endif
