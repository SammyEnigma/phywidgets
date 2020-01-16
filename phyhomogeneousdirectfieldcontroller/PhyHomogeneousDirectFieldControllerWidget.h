#ifndef PHYHOMOGENEOUSDIRECTFIELDCONTROLLERWIDGET_H
#define PHYHOMOGENEOUSDIRECTFIELDCONTROLLERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include "DirectionViewerGLWidget.h"
#include "HomogeneousFieldControllerWidget.h"

namespace phywidgets
{

class PhyHomogeneousDirectFieldControllerWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit PhyHomogeneousDirectFieldControllerWidget( QWidget* parent = nullptr );

    void setGLRotattionController( GLRotationControllerPtr gLRotationController );

    void setDirectionController( VectorControllerAdapterWeakPtr directionControllerWeak );
    void setScalarController( DoubleControllerAdapterWeakPtr scalarControllerWeak );

    void setHeader( const QString& header );
    void setScalarValueLabel( const QString& scalarValueLabel );

  private:
    QVBoxLayout* layout_ = nullptr;

    QVBoxLayout* aligmentGroupLayout_ = nullptr;
    QGroupBox* alignmentGroup_ = nullptr;

    QHBoxLayout* aligmentGlLayout_ = nullptr;
    QGroupBox* alignmentGl_ = nullptr;

    DirectionViewerGLWidget* directionViewerGLWidget_ = nullptr;
    HomogeneousFieldControllerWidget* homogeneousFieldControllerWidget_ = nullptr;
};

} // namespace phywidgets

#endif // PHYHOMOGENEOUSDIRECTFIELDCONTROLLERWIDGET_H
