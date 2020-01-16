#ifndef PHYREMOVEPARTICLEWIDGET_H
#define PHYREMOVEPARTICLEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "ParticleRemoveControllerAdapterIface.h"
#include "PhyRemoveParticlePhyCoubSubscriber.h"
#include "PhyCoubControllerSubscriberIface.h"

namespace phywidgets
{

class PhyRemoveParticleWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit PhyRemoveParticleWidget( QWidget* parent = nullptr );

    void setRemoveParticleControllerAdapter(
        ParticleRemoveControllerAdapter particleRemoveControllerAdapter );
    PhyCoubControllerSubscriberPtr getPhyCoubSubsriber();

  private slots:
    void removeParticle();

  protected:
    friend class PhyRemoveParticlePhyCoubSubscriber;

  private:
    void configureInputs();

    ParticleRemoveControllerAdapter particleRemoveControllerAdapter_ = nullptr;
    PhyRemoveParticlePhyCoubSubscriberPtr coubControllerSubscriber_ = nullptr;

    QHBoxLayout* layout_ = nullptr;

    QVBoxLayout* indexParticleLayout_ = nullptr;
    QLabel* indexParticleLabel_ = nullptr;
    QLineEdit* indexParticleEdit_ = nullptr;
    QPushButton* removeParticleButton_ = nullptr;
};

} // namespace phywidgets

#endif // PHYREMOVEPARTICLEWIDGET_H
