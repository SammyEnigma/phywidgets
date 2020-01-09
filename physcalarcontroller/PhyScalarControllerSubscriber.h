#ifndef PHYSCALARCONTROLLERSUBSCRIBER_H
#define PHYSCALARCONTROLLERSUBSCRIBER_H

#include <memory>
#include <mutex>

#include "PhyCoubControllerSubscriberIface.h"

namespace phywidgets
{

template< typename ValueType >
class PhyScalarControllerWidgetBase;

template< typename ValueType >
class PhyScalarControllerSubscriber : public PhyCoubControllerSubscriberIface
{
  public:
    PhyScalarControllerSubscriber( PhyScalarControllerWidgetBase< ValueType >* widget );
    virtual ~PhyScalarControllerSubscriber() override;

    // Implementation of PhyCoubControllerSubscriberIface
    virtual void onStart() override;
    virtual void onStop() override;

    void release();

  private:
    PhyScalarControllerWidgetBase< ValueType >* widget_;
    std::mutex widgetMutex_;
};

template< typename ValueType >
PhyScalarControllerSubscriber< ValueType >::PhyScalarControllerSubscriber(
    PhyScalarControllerWidgetBase< ValueType >* widget )
    : widget_( widget )
{
}

template< typename ValueType >
PhyScalarControllerSubscriber< ValueType >::~PhyScalarControllerSubscriber()
{
    release();
}

// virtual override
template< typename ValueType >
void PhyScalarControllerSubscriber< ValueType >::onStart()
{
    std::lock_guard< std::mutex > lockGuard( widgetMutex_ );
    if ( widget_ )
    {
        widget_->scalarValueEdit_->setDisabled( true );
    }
}

// virtual override
template< typename ValueType >
void PhyScalarControllerSubscriber< ValueType >::onStop()
{
    std::lock_guard< std::mutex > lockGuard( widgetMutex_ );
    if ( widget_ )
    {
        widget_->scalarValueEdit_->setDisabled( false );
    }
}

template< typename ValueType >
void PhyScalarControllerSubscriber< ValueType >::release()
{
    std::lock_guard< std::mutex > lockGuard( widgetMutex_ );
    widget_ = nullptr;
}

} // namespace phywidgets

#endif // PHYSCALARCONTROLLERSUBSCRIBER_H
