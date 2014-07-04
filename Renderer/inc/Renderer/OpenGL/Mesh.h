#ifndef __RENDERER_MESHOPENGL__
#define __RENDERER_MESHOPENGL__

#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <SOIL/SOIL.h>
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

class Mesh
{
  private:
    GLuint vao, vbo;
    int vertices_count;
  public:
    Mesh( std::string file_path );
    void configureShader( std::shared_ptr<Shader> shader );
    // getters
    GLuint getVAO() { return this->vao; }
    int getVerticesCount() { return this->vertices_count; }
};

#endif
