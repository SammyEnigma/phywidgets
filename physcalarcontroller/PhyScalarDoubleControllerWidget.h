#ifndef PHYSCALARCONTROLLER_H
#define PHYSCALARCONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "ScalarDoubleControllerAdapterIface.h"

namespace phywidgets
{

class PhyScalarDoubleControllerWidget : public QWidget
{
  public:
    PhyScalarDoubleControllerWidget( QWidget* parent = nullptr );

    void setScalarController( ScalarDoubleControllerAdapterPtr scalarControllerAdapter );
    void setScalarValueLabel( const QString& scalarValueLabel );

  private slots:
    void updateScalarValue( const QString& value );

  private:
    void configureScalarVaule();

    ScalarDoubleControllerAdapterPtr scalarConrollerAdapter_ = nullptr;

    QVBoxLayout* scalarLayout_ = nullptr;
    QLabel* scalarLabel_ = nullptr;
    QLineEdit* scalarValueEdit_ = nullptr;
};

} // namespace phywidgets

#endif // PHYSCALARCONTROLLER_H
