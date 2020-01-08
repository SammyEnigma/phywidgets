#ifndef PHYSCALARCONTROLLERWIDGETBASE_H
#define PHYSCALARCONTROLLERWIDGETBASE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "ScalarControllerAdapterIface.h"

namespace phywidgets
{

template< typename ValueType >
class PhyScalarControllerWidgetBase : public QWidget
{
  public:
    explicit PhyScalarControllerWidgetBase( QWidget* parent = nullptr );
    virtual ~PhyScalarControllerWidgetBase() = default;

    using ScalarTypeControllerAdapterPtr
        = std::shared_ptr< ScalarControllerAdapterIface< ValueType > >;

    void setScalarController( ScalarTypeControllerAdapterPtr scalarControllerAdapter );
    void setScalarValueLabel( const QString& scalarValueLabel );

  private slots:
    void updateScalarValue( const QString& value );

  protected:
    QVBoxLayout* getLayout();
    QLabel* getLabel();
    QLineEdit* getValueEdit();

  private:
    void configureScalarVaule();
    ScalarTypeControllerAdapterPtr scalarConrollerAdapter_ = nullptr;

    QVBoxLayout* scalarLayout_ = nullptr;
    QLabel* scalarLabel_ = nullptr;
    QLineEdit* scalarValueEdit_ = nullptr;
};

template< typename ValueType >
PhyScalarControllerWidgetBase< ValueType >::PhyScalarControllerWidgetBase(
    QWidget* parent )
    : QWidget( parent )
    , scalarLayout_( new QVBoxLayout( this ) )
    , scalarLabel_( new QLabel( this ) )
    , scalarValueEdit_( new QLineEdit( this ) )
{
    configureScalarVaule();
    setLayout( scalarLayout_ );

    QObject::connect( scalarValueEdit_, SIGNAL( textChanged( const QString& ) ), this,
        SLOT( updateScalarValue( const QString& ) ) );
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
void PhyScalarControllerWidgetBase< ValueType >::updateScalarValue( const QString& value )
{
    if ( scalarConrollerAdapter_ )
    {
        scalarConrollerAdapter_->setValue( value.toDouble() );
    }
}

template< typename ValueType >
QVBoxLayout* PhyScalarControllerWidgetBase< ValueType >::getLayout()
{
    return scalarLayout_;
}

template< typename ValueType >
QLabel* PhyScalarControllerWidgetBase< ValueType >::getLabel()
{
    return scalarLabel_;
}

template< typename ValueType >
QLineEdit* PhyScalarControllerWidgetBase< ValueType >::getValueEdit()
{
    return scalarValueEdit_;
}

template< typename ValueType >
void PhyScalarControllerWidgetBase< ValueType >::configureScalarVaule()
{
    scalarValueEdit_->setText( "0" );
    scalarLayout_->addWidget( scalarLabel_ );
    scalarLayout_->addWidget( scalarValueEdit_ );
}

} // namespace phywidgets

#endif // PHYSCALARCONTROLLERWIDGETBASE_H
