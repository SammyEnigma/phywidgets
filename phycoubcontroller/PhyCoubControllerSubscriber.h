#ifndef PHYCOUBCONTROLLERSUBSRIBER_H
#define PHYCOUBCONTROLLERSUBSRIBER_H

#include <memory>

#include "PhyCoubControllerSubscriberIface.h"

namespace phywidgets
{

class PhyCoubControllerWidget;

class PhyCoubControllerSubscriber final : public PhyCoubControllerSubscriberIface
{
  public:
    PhyCoubControllerSubscriber( PhyCoubControllerWidget* widget );
    virtual ~PhyCoubControllerSubscriber() override = default;

    // Implementation of PhyCoubControllerSubscriberIface
    virtual void onStart() override;
    virtual void onStop() override;

  private:
    PhyCoubControllerWidget* widget_;
};

} // namespace phywidgets

#endif // PHYCOUBCONTROLLERSUBSRIBER_H
