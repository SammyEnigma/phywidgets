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

  protected:
    virtual double toValueType( const QString& string ) override;

  private:
    void setValidator();
};

} // namespace phywidgets

#endif // PHYSCALARCONTROLLER_H
