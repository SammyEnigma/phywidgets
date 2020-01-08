#ifndef PHYSCALARCONTROLLER_H
#define PHYSCALARCONTROLLER_H

#include "PhyScalarControllerWidgetBase.h"

namespace phywidgets
{

class PhyScalarDoubleControllerWidget : public PhyScalarControllerWidgetBase< double >
{
  public:
    explicit PhyScalarDoubleControllerWidget( QWidget* parent = nullptr );
    virtual ~PhyScalarDoubleControllerWidget() override = default;

  private:
    void setValidator();
};

} // namespace phywidgets

#endif // PHYSCALARCONTROLLER_H
