#ifndef __WHITE_VIEWPORT__
#define __WHITE_VIEWPORT__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Renderer/Containable.h"
#include "Renderer/Scene.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "WMath/WMath.h"

class Viewport : public Containable<Viewport>
{
  private:
    std::vector< std::shared_ptr<Scene> > scenes;
  public:
    Viewport( ContainableData data );
    using Containable<Viewport>::setContainableCachedData;
    void setContainableCachedData( ContainableCachedData cached_data );
    void addScene( std::shared_ptr<Scene> scene );
    std::vector< std::shared_ptr<Scene> > getScenes() { return scenes; }
};

#endif
