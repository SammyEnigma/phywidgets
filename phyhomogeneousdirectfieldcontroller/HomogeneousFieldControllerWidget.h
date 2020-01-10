#ifndef HOMOGENIUSFIELDCONTROLLERWIDGET_H
#define HOMOGENIUSFIELDCONTROLLERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>

#include "ValueControllerAdapterIface.h"
#include "DirectionControllerWidget.h"

namespace phywidgets
{

class HomogeneousFieldControllerWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit HomogeneousFieldControllerWidget( QWidget* parent = nullptr );

    void setDirectionController( VectorControllerAdapterPtr directionController );
    void setScalarController( DoubleControllerAdapterPtr scalarController );

    void setScalarValueLabel( const QString& scalarValueLabel );

  private slots:
    void updateScalarValue( const QString& value );

  private:
    void configureScalarVaule();

    QHBoxLayout* layout_ = nullptr;

    QHBoxLayout* aligmentGroupLayout_ = nullptr;
    QGroupBox* alignmentGroup_ = nullptr;

    QVBoxLayout* scalarLayout_ = nullptr;
    QLabel* scalarLabel_ = nullptr;
    QLineEdit* scalarValueEdit_ = nullptr;
    DirectionControllerWidget* directionControllerWidget_ = nullptr;

    VectorControllerAdapterPtr directionController_ = nullptr;
    DoubleControllerAdapterPtr scalarController_ = nullptr;
};

} // namespace phywidgets

#endif // HOMOGENIUSFIELDCONTROLLERWIDGET_H
