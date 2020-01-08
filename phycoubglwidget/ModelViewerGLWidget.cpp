#include "ModelViewerGLWidget.h"

#include <QGL>
#include <QtGui>

namespace phywidgets
{

ModelViewerGLWidget::ModelViewerGLWidget( QWidget* parent /* = nullptr*/ )
    : QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
    , phyCoubGL( this )
{
    QObject::connect( &timerPlot_, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
    timerPlot_.start( 30 );
    gLRotationModelAdapter_ = std::make_shared< GLRotationModelAdapter >( this );
}

// virtual override
void ModelViewerGLWidget::updateGlRotation( int xRot, int yRot, int zRot )
{
    xRot_ = xRot;
    yRot_ = yRot;
    zRot_ = zRot;

    updateGL();
}

void ModelViewerGLWidget::setGetCoubSizeAdapter(
    GetCoubSizeAdapterPtr getCoubSizeAdapter )
{
    phyCoubGL.setGetCoubSizeAdapter( getCoubSizeAdapter );
    updateGL();
}

void ModelViewerGLWidget::setGetParticleForGLAdapter(
    GetParticlesForGLAdapterPtr getParticlesForGLAdapter )
{
    phyCoubGL.setGetParticleForGLAdapter( getParticlesForGLAdapter );
    updateGL();
}

void ModelViewerGLWidget::setGLRotationController(
    GLRotationControllerPtr gLRotationController )
{
    gLRotationController_ = gLRotationController;
    if ( gLRotationController_ )
    {
        gLRotationController_->subscribeForUpdates( gLRotationModelAdapter_ );
    }
}

void ModelViewerGLWidget::setXRotation( int angle )
{
    if ( gLRotationController_ )
    {
        gLRotationController_->updateRotationX( angle );
    }
}

void ModelViewerGLWidget::setYRotation( int angle )
{
    if ( gLRotationController_ )
    {
        gLRotationController_->updateRotationY( angle );
    }
}

void ModelViewerGLWidget::setZRotation( int angle )
{
    if ( gLRotationController_ )
    {
        gLRotationController_->updateRotationZ( angle );
    }
}

// virtual override
void ModelViewerGLWidget::initializeGL()
{
    qglClearColor( Qt::black );
}

// virtual override
void ModelViewerGLWidget::resizeGL( int width, int height )
{
    int side = qMin( width, height );
    glViewport( ( width - side ) / 2, ( height - side ) / 2, side, side );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof( -0.5, +0.5, -0.5, +0.5, 4.0, 15.0 );
#else
    glOrtho( -0.5, +0.5, -0.5, +0.5, 4.0, 15.0 );
#endif
    glMatrixMode( GL_MODELVIEW );
}

// virtual override
void ModelViewerGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -10.0 );

    glScaled( zoomScale_, zoomScale_, zoomScale_ );
    glRotatef( static_cast< float >( xRot_ / 16.0 ), 1.0, 0.0, 0.0 );
    glRotatef( static_cast< float >( yRot_ / 16.0 ), 0.0, 1.0, 0.0 );
    glRotatef( static_cast< float >( zRot_ / 16.0 ), 0.0, 0.0, 1.0 );

    phyCoubGL.updateScene();
}

// virtual override
void ModelViewerGLWidget::mousePressEvent( QMouseEvent* event )
{
    lastPos_ = event->pos();
}

// virtual override
void ModelViewerGLWidget::mouseMoveEvent( QMouseEvent* event )
{
    int dx = event->x() - lastPos_.x();
    int dy = event->y() - lastPos_.y();

    if ( event->buttons() & Qt::LeftButton )
    {
        setXRotation( xRot_ + 8 * dy );
        setYRotation( yRot_ + 8 * dx );
    }
    else if ( event->buttons() & Qt::RightButton )
    {
        setXRotation( xRot_ + 8 * dy );
        setZRotation( zRot_ + 8 * dx );
    }
    lastPos_ = event->pos();
}

// virtual override
void ModelViewerGLWidget::wheelEvent( QWheelEvent* event )
{
    QPoint numDegrees = event->angleDelta();
    if ( numDegrees.y() < 0 )
    {
        zoomScale_ = zoomScale_ / 1.1;
    }
    if ( numDegrees.y() > 0 )
    {
        zoomScale_ = zoomScale_ * 1.1;
    }
    updateGL();
}

} // namespace phywidgets