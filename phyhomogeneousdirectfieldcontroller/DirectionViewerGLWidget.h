#ifndef DIRECTIONVIEWERGLWIDGET_H
#define DIRECTIONVIEWERGLWIDGET_H

#include <QGLWidget>
#include <QTimer>

#include "GLRotationIface.h"
#include "GLRotationController.h"
#include "ValueControllerAdapterIface.h"
#include "Vector.h"
#include "GLRotationDirectionViewAdapter.h"

namespace phywidgets
{

class DirectionViewerGLWidget
    : public QGLWidget
    , public GLRotationIface
{
  public:
    DirectionViewerGLWidget( QWidget* parent = nullptr );

    // Implementation of GLRotationIface
    virtual void updateGlRotation( int xRot, int yRot, int zRot ) override;

    void setGLRotattionController( GLRotationControllerPtr gLRotationController );
    void setDirectionController( VectorControllerAdapterPtr directionController );

  public slots:
    void setXRotation( int angle );
    void setYRotation( int angle );
    void setZRotation( int angle );

  protected:
    friend class GLRotationDirectionViewAdapter;

    virtual void initializeGL() override;
    virtual void resizeGL( int width, int height ) override;
    virtual void paintGL() override;

    virtual void mousePressEvent( QMouseEvent* event ) override;
    virtual void mouseMoveEvent( QMouseEvent* event ) override;

  private:
    void drowCoordinateSystem();
    void drowDirectionVector();

    void drowSphere( const phycoub::Vector& coordinate, double radius );

    GLRotationControllerPtr gLRotationController_ = nullptr;
    VectorControllerAdapterPtr directionController_ = nullptr;
    std::shared_ptr< GLRotationDirectionViewAdapter > gLRotationDirectionViewAdapter_
        = nullptr;

    int xRot_ = 0;
    int yRot_ = 0;
    int zRot_ = 0;

    double zoomScale_ = 0.4;
    QPoint lastPos_;
    QTimer timerPlot_;

    static const phycoub::Vector origin_;
};

} // namespace phywidgets

#endif // DIRECTIONVIEWERGLWIDGET_H