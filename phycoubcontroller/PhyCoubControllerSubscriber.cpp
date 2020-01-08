#include "PhyCoubControllerSubscriber.h"

#include "PhyCoubControllerWidget.h"

namespace phywidgets
{

PhyCoubControllerSubscriber::PhyCoubControllerSubscriber(
    PhyCoubControllerWidget* widget )
    : widget_( widget )
{
}

// virtual override
void PhyCoubControllerSubscriber::onStart()
{
    if ( widget_ )
    {
        widget_->deltaTimeEdit_->setDisabled( true );
    }
}

// virtual override
void PhyCoubControllerSubscriber::onStop()
{
    if ( widget_ )
    {
        widget_->deltaTimeEdit_->setDisabled( false );
    }
}

} // namespace phywidgets
