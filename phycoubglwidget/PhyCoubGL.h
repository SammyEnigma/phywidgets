#ifndef PHYCOUBGL_H
#define PHYCOUBGL_H

#include <unordered_map>
#include <list>
#include <array>
#include <QColor>
#include <QGLWidget>
#include <QTableWidget>

#include "GetCoubSizeAdapterIface.h"
#include "GetParticlesForGLAdapterIface.h"
#include "Vector.h"
#include "ParticleGroup.h"

namespace phywidgets
{

class PhyCoubGL final
{
  public:
    PhyCoubGL( QGLWidget* gLWidget );
    ~PhyCoubGL() = default;

    void setGetCoubSizeAdapter( GetCoubSizeAdapterPtr getCoubSizeAdapter );
    void setGetParticleForGLAdapter(
        GetParticlesForGLAdapterPtr getParticlesForGLAdapter );
    void updateScene();

  private:
    void drowModelingCoub();
    void drowParticlesWithColorsByGroup(
        const phycoub::ParticleGroupList& particleGroupList );
    void drowVector( const phycoub::Vector& vector );
    void drowTrajectory();

    void drowSphere( const phycoub::Vector& coordinate, double radius );
    void drowCube( const phycoub::Vector& coordinate, double size );

    static phycoub::Vector mashtabVector(
        const phycoub::Vector& coordinate, const phycoub::Vector& mashtab );

    std::unordered_map< long int, std::list< phycoub::Vector > > trajectory_;

    std::weak_ptr< GetCoubSizeAdapterIface > getCoubSizeAdapterWeak_;
    std::weak_ptr< GetParticlesForGLAdapterIface > getParticlesForGLAdapterWeak_;

    QGLWidget* gLWidget_ = nullptr;
    phycoub::Vector coubSize_;

    static const phycoub::Vector origin_;
    constexpr static std::array< Qt::GlobalColor, 5 > colorsForGroup_
        = { Qt::green, Qt::red, Qt::blue, Qt::yellow, Qt::magenta };
};

} // namespace phywidgets

#endif // PHYCOUBGL_H
