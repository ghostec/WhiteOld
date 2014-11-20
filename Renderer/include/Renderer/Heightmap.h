#ifndef __WHITE_RENDERER_HEIGHTMAP__
#define __WHITE_RENDERER_HEIGHTMAP__

#include <string>
#include <vector>
#include "soil.h"
#include "WMath/WMath.h"
#include "Renderer/Mesh.h"

class Heightmap
{
  private:
    std::shared_ptr<Mesh> mesh;
  public:
    Heightmap( std::string file_path );
    std::shared_ptr<Mesh> getMesh() { return this->mesh; }
};

#endif