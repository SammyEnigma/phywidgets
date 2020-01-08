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

void PhyCoubController::startCalculation()
{
    if ( !isCalculating_ )
    {
        isCalculating_ = true;
        calculationThread_ = std::async( std::launch::async, [this]() {
            while ( isCalculating_ )
            {
                coub_->phyCoub();
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

void PhyCoubController::subscribe( PhyCoubControllerSubscriberPtr subscriber )
{
    subscribers_.push_back( subscriber );
}

} // namespace phywidgets
