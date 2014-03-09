#include "WMath/WMath.h"

namespace WMath
{

  mat4::mat4()
  {
    columns[0] = vec4( 1.0f, 0.0f, 0.0f, 0.0f );
    columns[1] = vec4( 0.0f, 1.0f, 0.0f, 0.0f );
    columns[2] = vec4( 0.0f, 0.0f, 1.0f, 0.0f );
    columns[3] = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
  }

  mat4::mat4( vec4 x, vec4 y, vec4 z, vec4 w )
  {
    columns[0] = x;
    columns[1] = y;
    columns[2] = z;
    columns[3] = w;
  }

  const vec4& mat4::operator[]( int index ) const
  {
    return columns[index];
  }
  vec4& mat4::operator[]( int index )
  {
    return columns[index];
  }

  vec4 operator*( const mat4& m, const vec4& v )
  {
    return vec4(
        m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
        m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
        );
  }

  vec4 operator*( const vec4& v, const mat4& m )
  {
    return vec4(
        v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
        v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
        );
  }

  mat4 operator*( const mat4& m1, const mat4& m2 )
  {
    vec4 X = m1 * m2[0];
    vec4 Y = m1 * m2[1];
    vec4 Z = m1 * m2[2];
    vec4 W = m1 * m2[3];

    return mat4( X, Y, Z, W );
  }

  mat4 translate( vec3 vector )
  {
    mat4 m;
    m[0][3] = vector[0];
    m[1][3] = vector[1];
    m[2][3] = vector[2];
    return m;
  }

  mat4 scale( vec3 vector )
  {
    mat4 m;
    m[0][0] = vector[0];
    m[1][1] = vector[1];
    m[2][2] = vector[2];
    m[3][3] = 1.0f;
    return m;
  }

  mat4 rotate_x( float degree )
  {
    mat4 m;
    m[1][1] = cos( degree * PI / 180.0 );
    m[1][2] = - sin( degree * PI / 180.0 );
    m[2][1] = sin( degree * PI / 180.0 );
    m[2][2] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 rotate_z( float degree )
  {
    mat4 m;
    m[0][0] = cos( degree * PI / 180.0 );
    m[0][1] = - sin( degree * PI / 180.0 );
    m[1][0] = sin( degree * PI / 180.0 );
    m[1][1] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 rotate_y( float degree )
  {
    mat4 m;
    m[0][0] = cos( degree * PI / 180.0 );
    m[0][2] = - sin( degree * PI / 180.0 );
    m[2][0] = sin( degree * PI / 180.0 );
    m[2][2] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 lookAtRH( vec3 eye, vec3 target, vec3 up )
  {
    vec3 zaxis = normalize( eye - target );       // The "forward" vector.
    vec3 xaxis = normalize( cross( up, zaxis ) ); // The "right" vector.
    vec3 yaxis = cross( zaxis, xaxis );           // The "up" vector.
    // Create a 4x4 orientation matrix from the right, up, and forward vectors
    // This is transposed which is equivalent to performing an inverse 
    // if the matrix is orthonormalized (in this case, it is).
    mat4 orientation(
      vec4( xaxis[0], yaxis[0], zaxis[0], 0 ),
      vec4( xaxis[1], yaxis[1], zaxis[1], 0 ),
      vec4( xaxis[2], yaxis[2], zaxis[2], 0 ),
      vec4(   0,       0,       0,     1 )
      );
    // Create a 4x4 translation matrix.
    // The eye position is negated which is equivalent
    // to the inverse of the translation matrix.
    // T(v)^-1 == T(-v)
    mat4 translation(
      vec4(   1,      0,      0,   0 ),
      vec4(   0,      1,      0,   0 ),
      vec4(   0,      0,      1,   0 ),
      vec4(-eye[0], -eye[1], -eye[2], 1 )
      );
    // Combine the orientation and translation to compute 
    // the final view matrix
    return ( orientation * translation );
  }

  float* value_ptr( mat4 *m )
  {
    return &m->columns[0][0];
  }

  mat4 OpenGlFrustum( float l, float r, float b, float t, float n, float f )
  {
    mat4 mat;

    mat[0][0] = 2.0f * n / (r - l);
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 0;

    mat[1][0] = 0;
    mat[1][1] = 2.0f * n / (t - b);
    mat[1][2] = 0;
    mat[1][3] = 0;

    mat[2][0] = (r + l) / (r - l);
    mat[2][1] = (t + b) / (t - b);
    mat[2][2] = -(f + n) / (f - n);
    mat[2][3] = -1.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = -2.0f * f * n / (f - n);
    mat[3][3] = 0.0f;

    return mat;
  }

  mat4 OpenGlPerspective( float angle, float imageAspectRatio, float n, float f )
  {
    float scale = tan( angle * 0.5 * PI / 180.0f ) * n;
    float r = imageAspectRatio * scale, l = -r;
    float t = scale, b = -t;
    return OpenGlFrustum( l, r, b, t, n, f );
  }

}
