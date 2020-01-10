#include "HomogeneousFieldControllerWidget.h"

namespace phywidgets
{

HomogeneousFieldControllerWidget::HomogeneousFieldControllerWidget( QWidget* parent )
    : QWidget( parent )
    , layout_( new QHBoxLayout( this ) )
    , aligmentGroupLayout_( new QHBoxLayout( this ) )
    , alignmentGroup_( new QGroupBox( tr( "Управление полем" ), this ) )
    , scalarLayout_( new QVBoxLayout( this ) )
    , scalarLabel_( new QLabel( this ) )
    , scalarValueEdit_( new QLineEdit( this ) )
    , directionControllerWidget_( new DirectionControllerWidget( this ) )
{
    configureScalarVaule();

    setLayout( layout_ );
    layout_->addWidget( alignmentGroup_ );

    alignmentGroup_->setLayout( aligmentGroupLayout_ );
    aligmentGroupLayout_->addLayout( scalarLayout_ );
    aligmentGroupLayout_->addWidget( directionControllerWidget_ );

    QObject::connect( scalarValueEdit_, SIGNAL( textChanged( const QString& ) ), this,
        SLOT( updateScalarValue( const QString& ) ) );
}

// virtual override
void HomogeneousFieldControllerWidget::setDirectionController(
    VectorControllerAdapterPtr directionController )
{
    directionControllerWidget_->setDirectionController( directionController );
}

// virtual override
void HomogeneousFieldControllerWidget::setScalarController(
    DoubleControllerAdapterPtr scalarController )
{
    scalarController_ = scalarController;
    if ( scalarController_ )
    {
        scalarValueEdit_->setText( QString::number( scalarController_->getValue() ) );
    }
}

void HomogeneousFieldControllerWidget::setScalarValueLabel(
    const QString& scalarValueLabel )
{
    scalarLabel_->setText( scalarValueLabel );
}

void HomogeneousFieldControllerWidget::updateScalarValue( const QString& value )
{
    if ( scalarController_ )
    {
        scalarController_->setValue( value.toDouble() );
    }
}

void HomogeneousFieldControllerWidget::configureScalarVaule()
{
    const QDoubleValidator* scalarValidator
        = new QDoubleValidator{ -3'000'000'000., 3'000'000'000., 2, this };
    scalarValueEdit_->setValidator( scalarValidator );
    scalarValueEdit_->setText( "0" );

    scalarLayout_->addWidget( scalarLabel_ );
    scalarLayout_->addWidget( scalarValueEdit_ );
}

} // namespace phywidgets
