#include "PhyScalarDoubleControllerWidget.h"

#include <QDoubleValidator>

namespace phywidgets
{

PhyScalarDoubleControllerWidget::PhyScalarDoubleControllerWidget( QWidget* parent )
    : PhyScalarControllerWidgetBase( parent )
{
    setValidator();
}

void PhyScalarDoubleControllerWidget::setValidator()
{
    const QDoubleValidator* scalarValidator
        = new QDoubleValidator{ -3'000'000'000., 3'000'000'000., 2, this };

    auto* valueEdit = getValueEdit();
    valueEdit->setValidator( scalarValidator );
}

// virtual override
double PhyScalarDoubleControllerWidget::toValueType( const QString& string )
{
    return string.toDouble();
}

} // namespace phywidgets
