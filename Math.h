#ifndef __WHITE_MATH__
#define __WHITE_MATH__

namespace Math
{
  class mat4
  {
    public:
      mat4();
      float mat[4][4];
  };

  class vec3
  {
    private:
    public:
      float x, y, z;
      vec3( float x = 0.0, float y = 0.0, float z = 0.0 );
  };

  vec3::vec3( float x, float y, float z )
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  mat4::mat4()
  {
    for( int i=0; i<4; i++ )
      for( int j=0; j<4; j++ )
        mat[i][j] = 0.0f;

    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.0f;
    mat[3][0] = 0.2f;
    mat[3][1] = 0.2f;
  }

  float* value_ptr( mat4 *m )
  {
    return &m->mat[0][0];
  }
}
#endif
