#ifndef GLROTTIONCONTROLLERVIEWADAPTER_H
#define GLROTTIONCONTROLLERVIEWADAPTER_H

#include <mutex>

#include "GLRotationIface.h"

namespace phywidgets
{

class DirectionViewerGLWidget;

class GLRotationDirectionViewAdapter final : public GLRotationIface
{
  public:
    GLRotationDirectionViewAdapter( DirectionViewerGLWidget* widget );
    virtual ~GLRotationDirectionViewAdapter() override;

    // Implementation of GLRotationIface
    virtual void updateGlRotation( int xRot, int yRot, int zRot ) override;

    void release();

  private:
    DirectionViewerGLWidget* widget_;
    std::mutex widgetMutex_;
};

} // namespace phywidgets

#endif // GLROTTIONCONTROLLERVIEWADAPTER_H
