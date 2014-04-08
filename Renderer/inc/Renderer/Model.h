#ifndef __WHITE_MODEL__
#define __WHITE_MODEL__

#include "WMath/WMath.h"

typedef struct _ModelCommon
{
  WMath::mat4 transformation;
  int vertices_count;
} ModelCommon;

#ifndef _OPENGL_
#include "Renderer/OpenGL/Model.h"
#endif

#endif