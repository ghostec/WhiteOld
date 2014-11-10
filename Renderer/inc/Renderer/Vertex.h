#ifndef __WHITE_RENDERER_VERTEX__
#define __WHITE_RENDERER_VERTEX__

#include <vector>
#include "WMath/WMath.h"

enum VertexType
{
  VERTEX_3, VERTEX_3N, VERTEX_3T, VERTEX_3NT
};

class Vertex
{
  private:
    WMath::vec3 v, n, t;
    VertexType type;
  public:
    // setters
    void setVertex( WMath::vec3 v ) { this->v = v; }
    // getters
    WMath::vec3 getVertex() { return this->v; }
};

#endif
