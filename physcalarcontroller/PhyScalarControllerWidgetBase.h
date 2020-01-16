#ifndef PHYSCALARCONTROLLERWIDGETBASE_H
#define PHYSCALARCONTROLLERWIDGETBASE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "ValueControllerAdapterIface.h"
#include "PhyScalarPhyCoubControllerSubscriber.h"
#include "PhyCoubController.h"

namespace phywidgets
{

template< typename ValueType >
class PhyScalarControllerWidgetBase : public QWidget
{
  public:
    explicit PhyScalarControllerWidgetBase( QWidget* parent = nullptr );
    virtual ~PhyScalarControllerWidgetBase();

    using ScalarTypeControllerAdapterPtr
        = std::shared_ptr< ValueControllerAdapterIface< ValueType > >;

    void setScalarController( ScalarTypeControllerAdapterPtr scalarControllerAdapter );
    void setScalarValueLabel( const QString& scalarValueLabel );

    void setPhyCoubController( PhyCoubControllerPtr phyCoubController );

  protected:
    friend class PhyScalarPhyCoubControllerSubscriber< ValueType >;

    QLineEdit* getValueEdit();
    QPushButton* getSetValueButton();
    ScalarTypeControllerAdapterPtr getScalarControllerAdapter();

    QPushButton* setScalarValueButton_ = nullptr;

  private:
    void configureScalarVaule();
    ScalarTypeControllerAdapterPtr scalarConrollerAdapter_ = nullptr;

    std::weak_ptr< PhyCoubController > phyCoubControllerWeak_;
    PhyScalarPhyCoubControllerSubscriberPtr< ValueType > controllerSubscriber_ = nullptr;

    QHBoxLayout* scalarLayout_ = nullptr;
    QVBoxLayout* scalarEditLayout_ = nullptr;
    QLabel* scalarLabel_ = nullptr;
    QLineEdit* scalarValueEdit_ = nullptr;
};

template< typename ValueType >
PhyScalarControllerWidgetBase< ValueType >::PhyScalarControllerWidgetBase(
    QWidget* parent )
    : QWidget( parent )
    , scalarLayout_( new QHBoxLayout( this ) )
    , scalarEditLayout_( new QVBoxLayout( this ) )
    , scalarLabel_( new QLabel( this ) )
    , scalarValueEdit_( new QLineEdit( this ) )
    , setScalarValueButton_( new QPushButton( this ) )
    , controllerSubscriber_(
          std::make_shared< PhyScalarPhyCoubControllerSubscriber< ValueType > >( this ) )
{
    configureScalarVaule();
    setLayout( scalarLayout_ );
}

template< typename ValueType >
PhyScalarControllerWidgetBase< ValueType >::~PhyScalarControllerWidgetBase()
{
    controllerSubscriber_->release();
}

template< typename ValueType >
void PhyScalarControllerWidgetBase< ValueType >::setScalarController(
    ScalarTypeControllerAdapterPtr scalarConrollerAdapter )
{
    scalarConrollerAdapter_ = scalarConrollerAdapter;
    if ( scalarConrollerAdapter_ )
    {
        scalarValueEdit_->setText(
            QString::number( scalarConrollerAdapter_->getValue() ) );
    }
}

template< typename ValueType >
void PhyScalarControllerWidgetBase< ValueType >::setScalarValueLabel(
    const QString& scalarValueLabel )
{
    scalarLabel_->setText( scalarValueLabel );
}

template< typename ValueType >
void PhyScalarControllerWidgetBase< ValueType >::setPhyCoubController(
    PhyCoubControllerPtr phyCoubController )
{
    phyCoubControllerWeak_ = phyCoubController;
    if ( auto phyCoubController = phyCoubControllerWeak_.lock() )
    {
        phyCoubController->subscribe( controllerSubscriber_ );
    }
}

template< typename ValueType >
QLineEdit* PhyScalarControllerWidgetBase< ValueType >::getValueEdit()
{
    return scalarValueEdit_;
}

template< typename ValueType >
QPushButton* PhyScalarControllerWidgetBase< ValueType >::getSetValueButton()
{
    return setScalarValueButton_;
}

template< typename ValueType >
typename PhyScalarControllerWidgetBase< ValueType >::ScalarTypeControllerAdapterPtr
PhyScalarControllerWidgetBase< ValueType >::getScalarControllerAdapter()
{
    return scalarConrollerAdapter_;
}

template< typename ValueType >
void PhyScalarControllerWidgetBase< ValueType >::configureScalarVaule()
{
    scalarLayout_->addLayout( scalarEditLayout_ );
    scalarLayout_->addWidget( setScalarValueButton_ );

    scalarEditLayout_->addWidget( scalarLabel_ );
    scalarEditLayout_->addWidget( scalarValueEdit_ );

    setScalarValueButton_->setText( "Установить" );
}

} // namespace phywidgets

#endif // PHYSCALARCONTROLLERWIDGETBASE_H
