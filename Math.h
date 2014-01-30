#ifndef __WHITE_MATH__
#define __WHITE_MATH__

class Vector3
{
  private:
  public:
    float x, y, z;
    Vector3( float x = 0.0, float y = 0.0, float z = 0.0 );
};

Vector3::Vector3( float x, float y, float z )
{
  this->x = x;
  this->y = y;
  this->z = z;
}

#endif
