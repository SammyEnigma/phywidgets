#include "PhyScalarULongControllerWidget.h"

#include <QIntValidator>

namespace phywidgets
{

PhyScalarULongControllerWidget::PhyScalarULongControllerWidget( QWidget* parent )
    : PhyScalarControllerWidgetBase( parent )
{
    setValidator();
}

void PhyScalarULongControllerWidget::setValidator()
{
    const QIntValidator* scalarValidator = new QIntValidator{ 0, 1'000'000, this };

    auto* valueEdit = getValueEdit();
    valueEdit->setValidator( scalarValidator );
}

// virtual override
long PhyScalarULongControllerWidget::toValueType( const QString& string )
{
    return string.toLong();
}

} // namespace phywidgets
