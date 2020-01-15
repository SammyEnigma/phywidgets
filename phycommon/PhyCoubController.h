#ifndef PHYCOUBCONTROLLER_H
#define PHYCOUBCONTROLLER_H

#include <mutex>
#include <future>
#include <memory>

#include "PhyCoub.h"
#include "PhyCoubControllerSubscriberIface.h"
#include "GetParticlesAdapterIface.h"

namespace phywidgets
{

class PhyCoubController final : public GetParticlesAdapterIface
{
  public:
    PhyCoubController( phycoub::PhyCoubPtr coub );
    virtual ~PhyCoubController() override;

    // Implementation of GetParticlesForGLAdapterIface
    virtual phycoub::ParticleGroupList getParticles() const override;

    void startCalculation();
    void calculateOnce();
    void stopCalculation();

    void setDeltaTime( double dt );
    double getDeltaTime() const;

    double getExperimentTime() const;
    void resetToZeroExperimentTime();

    void subscribe( PhyCoubControllerSubscriberPtr subscriber );

  private:
    phycoub::ParticleGroupList particlesForGL_;
    mutable std::mutex particlesForGLMutex_;

    bool isCalculating_ = false;
    std::future< void > calculationThread_;
    phycoub::PhyCoubPtr coub_;

    std::list< std::weak_ptr< PhyCoubControllerSubscriberIface > > subscribers_;
};

using PhyCoubControllerPtr = std::shared_ptr< PhyCoubController >;

} // namespace phywidgets

#endif // PHYCOUBCONTROLLER_H
