#ifndef PHYCOUBCONTROLLER_H
#define PHYCOUBCONTROLLER_H

#include <future>
#include <memory>

#include "PhyCoub.h"
#include "PhyCoubControllerSubscriberIface.h"

namespace phywidgets
{

class PhyCoubController final
{
  public:
    PhyCoubController( phycoub::PhyCoubPtr coub );
    ~PhyCoubController();

    void startCalculation();
    void calculateOnce();
    void stopCalculation();

    void setDeltaTime( double dt );
    double getDeltaTime() const;

    double getExperimentTime() const;
    void resetToZeroExperimentTime();

    void subscribe( PhyCoubControllerSubscriberPtr subscriber );

  private:
    bool isCalculating_ = false;
    std::future< void > calculationThread_;
    phycoub::PhyCoubPtr coub_;

    std::list< std::weak_ptr< PhyCoubControllerSubscriberIface > > subscribers_;
};

using PhyCoubControllerPtr = std::shared_ptr< PhyCoubController >;

} // namespace phywidgets

#endif // PHYCOUBCONTROLLER_H
