#ifndef PHYADDPARTICLEWIDGET_H
#define PHYADDPARTICLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "AddParticleControllerAdapterIface.h"
#include "GetCoubSizeAdapterIface.h"

namespace phywidgets
{

class PhyAddParticleWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit PhyAddParticleWidget( QWidget* parent = nullptr );

    void setAddParticleControllerAdapter(
        AddParticleControllerAdapterPtr addParticleControllerAdapter );
    void setGetCoubSizeAdapter( GetCoubSizeAdapterPtr getCoubSizeAdapter );

    void setDefaultOptions( ParticleOptions options );

  private slots:
    void addParticle();

  private:
    void configureInputs();

    ParticleOptions defaultParticleOptions_;

    AddParticleControllerAdapterPtr addParticleControllerAdapter_ = nullptr;
    GetCoubSizeAdapterPtr getCoubSizeAdapter_ = nullptr;

    QHBoxLayout* addParticleLayout_ = nullptr;

    QVBoxLayout* coordinateXLayout_ = nullptr;
    QVBoxLayout* coordinateYLayout_ = nullptr;
    QVBoxLayout* coordinateZLayout_ = nullptr;

    QLabel* coordinateXLabel_ = nullptr;
    QLabel* coordinateYLabel_ = nullptr;
    QLabel* coordinateZLabel_ = nullptr;

    QLineEdit* coordinateXParticleEdit_ = nullptr;
    QLineEdit* coordinateYParticleEdit_ = nullptr;
    QLineEdit* coordinateZParticleEdit_ = nullptr;

    QVBoxLayout* speedXLayout_ = nullptr;
    QVBoxLayout* speedYLayout_ = nullptr;
    QVBoxLayout* speedZLayout_ = nullptr;

    QLabel* speedXLabel_ = nullptr;
    QLabel* speedYLabel_ = nullptr;
    QLabel* speedZLabel_ = nullptr;

    QLineEdit* speedXParticleEdit_ = nullptr;
    QLineEdit* speedYParticleEdit_ = nullptr;
    QLineEdit* speedZParticleEdit_ = nullptr;

    QVBoxLayout* weightLayout_ = nullptr;
    QVBoxLayout* chargeLayout_ = nullptr;

    QLabel* weightLabel_ = nullptr;
    QLabel* chargeLabel_ = nullptr;

    QLineEdit* weightParticleEdit_ = nullptr;
    QLineEdit* chargeParticleEdit_ = nullptr;

    QPushButton* addParticleButton_ = nullptr;
};

} // namespace phywidgets

#endif // PHYADDPARTICLEWIDGET_H
