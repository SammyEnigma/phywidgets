#include "PhyCoubController.h"

namespace phywidgets
{

PhyCoubController::PhyCoubController( phycoub::PhyCoubPtr coub )
    : coub_( coub )
{
}

PhyCoubController::~PhyCoubController()
{
    stopCalculation();
}

// virtual override
phycoub::ParticleGroupList PhyCoubController::getParticles() const
{
    std::lock_guard< std::mutex > lockGuard( particlesForGLMutex_ );
    return particlesForGL_;
}

void PhyCoubController::startCalculation()
{
    if ( !isCalculating_ )
    {
        isCalculating_ = true;
        calculationThread_ = std::async( std::launch::async, [this]() {
            while ( isCalculating_ )
            {
                coub_->phyCoub();
                {
                    std::lock_guard< std::mutex > lockGuard( particlesForGLMutex_ );
                    particlesForGL_ = coub_->getParticleGroupList().deepCopy();
                }
            }
        } );
        for ( auto subscriberWeak : subscribers_ )
        {
            if ( auto subscriber = subscriberWeak.lock() )
            {
                subscriber->onStart();
            }
        }
    }
}

void PhyCoubController::stopCalculation()
{
    if ( isCalculating_ )
    {
        isCalculating_ = false;
        calculationThread_.get();
        for ( auto subscriberWeak : subscribers_ )
        {
            if ( auto subscriber = subscriberWeak.lock() )
            {
                subscriber->onStop();
            }
        }
    }
}

void PhyCoubController::calculateOnce()
{
    if ( !isCalculating_ )
    {
        coub_->phyCoub();
    }
}

void PhyCoubController::setDeltaTime( double dt )
{
    coub_->setDeltaTime( dt );
}

double PhyCoubController::getDeltaTime() const
{
    return coub_->getDeltaTime();
}

double PhyCoubController::getExperimentTime() const
{
    return coub_->getExperimentTime();
}

void PhyCoubController::resetToZeroExperimentTime()
{
    coub_->resetToZeroExperimentTime();
}

void PhyCoubController::subscribe( PhyCoubControllerSubscriberWeakPtr subscriber )
{
    subscribers_.push_back( subscriber );
}

} // namespace phywidgets
