#ifndef SCALARVALUECONTROLLERADAPTERIFACE_H
#define SCALARVALUECONTROLLERADAPTERIFACE_H

#include <memory>

namespace phywidgets
{

class ScalarDoubleControllerAdapterIface
{
  public:
    virtual ~ScalarDoubleControllerAdapterIface() = default;

    virtual double getValue() = 0;
    virtual void setValue( double value ) = 0;
};

using ScalarDoubleControllerAdapterPtr
    = std::shared_ptr< ScalarDoubleControllerAdapterIface >;

} // namespace phywidgets

#endif // SCALARVALUECONTROLLERADAPTERIFACE_H
