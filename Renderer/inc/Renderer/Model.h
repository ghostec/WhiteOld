#ifndef __WHITE_MODEL__
#define __WHITE_MODEL__

#include <iostream>
#include <string>
#include "WMath/WMath.h"
#include "Renderer/ModelHelper.h"

typedef enum _ModelFileType { OBJ } ModelFileType;

class Model
{
  public:
    virtual void draw() = 0;
    virtual void translate( WMath::vec3 vector ) = 0;
    virtual void scale( WMath::vec3 vector ) = 0;
    virtual void rotate( float degrees ) = 0;
};

#endif
