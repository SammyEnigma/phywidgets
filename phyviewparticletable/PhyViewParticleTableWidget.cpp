#include "PhyViewParticleTableWidget.h"

#include <QHeaderView>

namespace phywidgets
{

PhyViewParticleTableWidget::PhyViewParticleTableWidget( QWidget* parent /* = nullptr*/ )
    : QWidget( parent )
    , layout_( new QVBoxLayout( this ) )
    , tableWidget_( new QTableWidget( this ) )
{
    initializeTableWidget();

    setLayout( layout_ );
    layout_->addWidget( tableWidget_ );

    QObject::connect(
        &timerPlot_, SIGNAL( timeout() ), this, SLOT( updateParticleTable() ) );

    timerPlot_.start( 100 );
}

void PhyViewParticleTableWidget::setGetParticleAdapter(
    GetParticlesForGLAdapterPtr getParticlesForGLAdapter )
{
    getParticlesForGLAdapter_ = getParticlesForGLAdapter;
}

void PhyViewParticleTableWidget::setGetCoubSizeAdapter(
    GetCoubSizeAdapterPtr getCoubSizeAdapter )
{
    getCoubSizeAdapter_ = getCoubSizeAdapter;
}

void PhyViewParticleTableWidget::updateParticleTable()
{
    using namespace phycoub;

    if ( getParticlesForGLAdapter_ && getCoubSizeAdapter_ )
    {
        const Vector& coubSize = getCoubSizeAdapter_->getCoubSize();

        const ParticleGroupList& particleGroupList
            = getParticlesForGLAdapter_->getParticles();

        tableWidget_->setRowCount(
            static_cast< int >( particleGroupList.getParticleCount() ) );

        int rowIndex = 0;
        for ( const ParticlePtr& particle : particleGroupList )
        {
            tableWidget_->setItem( rowIndex, 0,
                new QTableWidgetItem( QString::number( particle->getId() ) ) );

            const Vector& coordinate = particle->getCoordinate();
            tableWidget_->setItem( rowIndex, 1,
                new QTableWidgetItem( QString::number( coordinate.x_ / coubSize.x_ ) ) );
            tableWidget_->setItem( rowIndex, 2,
                new QTableWidgetItem( QString::number( coordinate.y_ / coubSize.y_ ) ) );
            tableWidget_->setItem( rowIndex, 3,
                new QTableWidgetItem( QString::number( coordinate.z_ / coubSize.z_ ) ) );

            const Vector& speed = particle->getSpeed();
            tableWidget_->setItem(
                rowIndex, 4, new QTableWidgetItem( QString::number( speed.x_ ) ) );
            tableWidget_->setItem(
                rowIndex, 5, new QTableWidgetItem( QString::number( speed.y_ ) ) );
            tableWidget_->setItem(
                rowIndex, 6, new QTableWidgetItem( QString::number( speed.z_ ) ) );

            const ParticleOptions options = particle->getOptions();
            tableWidget_->setItem(
                rowIndex, 7, new QTableWidgetItem( QString::number( options.m_ ) ) );
            tableWidget_->setItem(
                rowIndex, 8, new QTableWidgetItem( QString::number( options.q_ ) ) );

            ++rowIndex;
        }
    }
}

void PhyViewParticleTableWidget::initializeTableWidget()
{
    static const QStringList headers = { tr( "Идентификатор" ), tr( "Координата X" ),
        tr( "Координата Y" ), tr( "Координата Z" ), tr( "Пр. скорости X [м/c]" ),
        tr( "Пр. скорости Y [м/c]" ), tr( "Пр. скорости Z [м/c]" ), tr( "Масса [кг]" ),
        tr( "Заряд [Кл]" ) };

    tableWidget_->setColumnCount( headers.size() );
    tableWidget_->setHorizontalHeaderLabels( headers );

    tableWidget_->setEditTriggers( QAbstractItemView::NoEditTriggers );
    tableWidget_->horizontalHeader()->setStretchLastSection( true );
    tableWidget_->verticalHeader()->hide();

    tableWidget_->setSelectionMode( QAbstractItemView::SingleSelection );
    tableWidget_->setSelectionBehavior( QAbstractItemView::SelectRows );
}

} // namespace phywidgets
