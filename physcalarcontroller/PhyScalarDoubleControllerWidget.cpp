#include "PhyScalarDoubleControllerWidget.h"

#include <QDoubleValidator>

namespace phywidgets
{

PhyScalarDoubleControllerWidget::PhyScalarDoubleControllerWidget( QWidget* parent )
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

void PhyScalarDoubleControllerWidget::setScalarController(
    ScalarDoubleControllerAdapterPtr scalarConrollerAdapter )
{
    scalarConrollerAdapter_ = scalarConrollerAdapter;
    if ( scalarConrollerAdapter_ )
    {
        scalarValueEdit_->setText(
            QString::number( scalarConrollerAdapter_->getValue() ) );
    }
}

void PhyScalarDoubleControllerWidget::setScalarValueLabel(
    const QString& scalarValueLabel )
{
    scalarLabel_->setText( scalarValueLabel );
}

void PhyScalarDoubleControllerWidget::updateScalarValue( const QString& value )
{
    if ( scalarConrollerAdapter_ )
    {
        scalarConrollerAdapter_->setValue( value.toDouble() );
    }
}

void PhyScalarDoubleControllerWidget::configureScalarVaule()
{
    const QDoubleValidator* scalarValidator
        = new QDoubleValidator{ -3'000'000'000., 3'000'000'000., 2, this };
    scalarValueEdit_->setValidator( scalarValidator );
    scalarValueEdit_->setText( "0" );

    scalarLayout_->addWidget( scalarLabel_ );
    scalarLayout_->addWidget( scalarValueEdit_ );
}

} // namespace phywidgets
