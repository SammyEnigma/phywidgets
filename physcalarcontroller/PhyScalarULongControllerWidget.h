#ifndef PHYSCALARLONGCONTROLLERWIDGET_H
#define PHYSCALARLONGCONTROLLERWIDGET_H

#include "PhyScalarControllerWidgetBase.h"

namespace phywidgets
{

class PhyScalarULongControllerWidget : public PhyScalarControllerWidgetBase< long >
{
  public:
    explicit PhyScalarULongControllerWidget( QWidget* parent = nullptr );
    virtual ~PhyScalarULongControllerWidget() override = default;

  protected:
    virtual long toValueType( const QString& string ) override;

  private:
    void setValidator();
};

} // namespace phywidgets

#endif // PHYSCALARLONGCONTROLLERWIDGET_H
