#ifndef __WMATH_WMATH__
#define __WMATH_WMATH__

#include <iostream>
#include <memory>
#include <cmath>

#define PI 3.14159265

namespace WMath
{

  class vec2; class vec3; class vec4;

  class vec2
  {
    public:
      float vec[2];
      vec2();
      vec2( float a );
      vec2( float x, float y );
      const float& operator[] ( int index ) const;
      float& operator[] ( int index );
  };

  class vec3
  {
  public:
    float vec[3];
    vec3( );
    vec3( float a );
    vec3( float x, float y, float z );
    vec3( vec4 v );
    const float& operator[] ( int index ) const;
    float& operator[] ( int index );
  };

  class vec4
  {
    public:
      float vec[4];
      vec4();
      vec4( float a );
      vec4( float x, float y, float z, float w );
      vec4( vec3 v, float w );
      vec4( float x, vec3 v );
      const float& operator[] ( int index ) const;
      float& operator[] ( int index );
  };

  class mat4
  {
    public:
      vec4 columns[4];
      mat4();
      mat4( vec4 x, vec4 y, vec4 z, vec4 w );
      const vec4& operator[]( int index ) const;
      vec4& operator[]( int index );
  };

  class quaternion
  {
    public:
      float vec[4];
      quaternion();
      quaternion( float x, float y, float z, float degrees );
      quaternion( vec3 v, float degrees );
      const float& operator[] ( int index ) const;
      float& operator[] ( int index );
  };

  vec2 operator*( const float& f, const vec2& v );
  vec2 operator*( const vec2& v, const float& f );
  vec2 operator+( const vec2& v1, const vec2& v2 );
  vec2 operator-( const vec2& v1, const vec2& v2 );
  bool operator<( const vec2& v1, const vec2& v2 );
  bool operator<=( const vec2& v1, const vec2& v2 );
  bool operator>( const vec2& v1, const vec2& v2 );
  bool operator>=( const vec2& v1, const vec2& v2 );

  vec3 operator*( const float& f, const vec3& v );
  vec3 operator*( const vec3& v, const float& f );
  vec3 operator+( const vec3& v1, const vec3& v2 );
  vec3 operator+=( vec3& v1, const vec3& v2 );
  vec3 operator-( const vec3& v1, const vec3& v2 );
  vec3 operator-( const vec3& v );

  vec4 operator*( const mat4& m, const vec4& v );
  vec4 operator*( const vec4& v, const mat4& m );
  mat4 operator*( const mat4& m1, const mat4& m2 );

  quaternion operator*( const quaternion& q1, const quaternion& q2 );

  mat4 lookAtRH( vec3 eye, vec3 target, vec3 up );
  mat4 OpenGlFrustum( float l, float r, float b, float t, float n, float f );
  mat4 OpenGlPerspective( float angle, float imageAspectRatio, float n, float f );

  float dot( vec4 v1, vec4 v2 );
  vec4 normalize( vec4 v );

  float dot( vec3 v1, vec3 v2 );
  vec3 normalize( vec3 v );
  vec3 cross( vec3 v1, vec3 v2 );

  quaternion normalize( quaternion v );

  float* value_ptr( mat4* m );

  bool isPointInside
  ( WMath::vec2 anchor, WMath::vec2 dimensions, WMath::vec2 point );
}
#endif
