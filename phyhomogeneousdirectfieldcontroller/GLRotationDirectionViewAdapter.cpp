#include "GLRotationDirectionViewAdapter.h"

#include "DirectionViewerGLWidget.h"

namespace phywidgets
{

GLRotationDirectionViewAdapter::GLRotationDirectionViewAdapter(
    DirectionViewerGLWidget* widget )
    : widget_( widget )
{
}

GLRotationDirectionViewAdapter::~GLRotationDirectionViewAdapter()
{
    release();
}

// virtual override
void GLRotationDirectionViewAdapter::updateGlRotation( int xRot, int yRot, int zRot )
{
    std::lock_guard< std::mutex > lockGuard( widgetMutex_ );

    widget_->xRot_ = xRot;
    widget_->yRot_ = yRot;
    widget_->zRot_ = zRot;

    widget_->updateGL();
}

void GLRotationDirectionViewAdapter::release()
{
    std::lock_guard< std::mutex > lockGuard( widgetMutex_ );
    widget_ = nullptr;
}

} // namespace phywidgets
