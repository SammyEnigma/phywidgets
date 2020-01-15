#ifndef PHYVIEWPARTICLETABLEWIDGET_H
#define PHYVIEWPARTICLETABLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

#include "GetParticlesForGLAdapterIface.h"
#include "GetCoubSizeAdapterIface.h"

namespace phywidgets
{

class PhyViewParticleTableWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit PhyViewParticleTableWidget( QWidget* parent = nullptr );

    void setGetParticleAdapter( GetParticlesForGLAdapterPtr getParticlesForGLAdapter );
    void setGetCoubSizeAdapter( GetCoubSizeAdapterPtr getCoubSizeAdapter );

  private slots:
    void updateParticleTable();

  private:
    void initializeTableWidget();

    GetParticlesForGLAdapterPtr getParticlesForGLAdapter_ = nullptr;
    GetCoubSizeAdapterPtr getCoubSizeAdapter_ = nullptr;

    QTimer timerPlot_;

    QVBoxLayout* layout_ = nullptr;
    QTableWidget* tableWidget_ = nullptr;
};

} // namespace phywidgets

#endif // PHYVIEWPARTICLETABLEWIDGET_H
