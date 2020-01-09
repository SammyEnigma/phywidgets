#include <QOpenGLFunctions>
#include <QGL>
#include <GL/glu.h>

#include "PhyCoubGL.h"
#include "ParticleGroup.h"

namespace phywidgets
{

// static
const phycoub::Vector PhyCoubGL::origin_ = phycoub::Vector{ 0.5, 0.5, 0.5 };

PhyCoubGL::PhyCoubGL( QGLWidget* gLWidget )
    : gLWidget_( gLWidget )
{
}

void PhyCoubGL::setGetCoubSizeAdapter( GetCoubSizeAdapterPtr getCoubSizeAdapter )
{
    getCoubSizeAdapterWeak_ = getCoubSizeAdapter;
    coubSize_ = getCoubSizeAdapter->getCoubSize();
}

void PhyCoubGL::setGetParticleForGLAdapter(
    GetParticlesForGLAdapterPtr getParticlesForGLAdapter )
{
    getParticlesForGLAdapterWeak_ = getParticlesForGLAdapter;
}

void PhyCoubGL::updateScene()
{
    if ( auto getParticlesForGLAdapter = getParticlesForGLAdapterWeak_.lock() )
    {
        drowModelingCoub();
        drowParticlesWithColorsByGroup( getParticlesForGLAdapter->getParticles() );
        drowTrajectory();
    }
}

void PhyCoubGL::drowModelingCoub()
{
    gLWidget_->qglColor( Qt::white );
    drowCube( phycoub::Vector{ 0, 0, 0 }, 1 );
}

void PhyCoubGL::drowParticlesWithColorsByGroup(
    const phycoub::ParticleGroupList& particleGroupList )
{
    using namespace phycoub;
    size_t colorIndex = 0;

    for ( ParticleGroupList::GroupConstIterator groupIterator
          = particleGroupList.beginGroup();
          groupIterator != particleGroupList.endGroup(); ++groupIterator )
    {
        gLWidget_->qglColor( colorsForGroup_[ colorIndex ] );

        for ( ParticlePtr particle : **groupIterator )
        {
            const Vector& particleCoordinate = particle->getCoordinate();
            const Vector mashtabedOriginCoordinate
                = mashtabVector( particleCoordinate, coubSize_ ) - origin_;
            drowSphere( mashtabedOriginCoordinate, 0.01 );
            /*
                        auto& trajectoryVector = trajectory_[ particle->getId() ];
                        trajectoryVector.push_back( mashtabedOriginCoordinate );
                        if ( trajectoryVector.size() > 100 )
                        {
                            trajectoryVector.pop_front();
                        }
            */
        }
        ++colorIndex;
    }
}

void PhyCoubGL::drowTrajectory()
{
    gLWidget_->qglColor( Qt::cyan );
    for ( const auto& particleTrajectory : trajectory_ )
    {
        for ( const auto& coordinateOfTrajectory : particleTrajectory.second )
        {
            drowSphere( coordinateOfTrajectory, 0.001 );
        }
    }
}

void PhyCoubGL::drowSphere( const phycoub::Vector& coordinate, double radius )
{
    glPushMatrix();
    glScalef( 1, 1, 1 );
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricNormals( quadric, GLU_SMOOTH );
    gluQuadricDrawStyle( quadric, GLU_LINE );
    glTranslatef( static_cast< float >( coordinate.x_ ),
        static_cast< float >( coordinate.y_ ), static_cast< float >( coordinate.z_ ) );
    gluSphere( quadric, radius, 36, 36 );
    gluDeleteQuadric( quadric );
    glPopMatrix();
}

void PhyCoubGL::drowCube( const phycoub::Vector& coordinate, double size )
{
    glLineWidth( 2.0f );
    glBegin( GL_LINES );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    //
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    //
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ - 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ + 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );

    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ + 0.5 * size ) );
    glVertex3f( static_cast< float >( coordinate.x_ + 0.5 * size ),
        static_cast< float >( coordinate.y_ - 0.5 * size ),
        static_cast< float >( coordinate.z_ - 0.5 * size ) );
    glEnd();
}

// static
phycoub::Vector PhyCoubGL::mashtabVector(
    const phycoub::Vector& coordinate, const phycoub::Vector& mashtab )
{
    const phycoub::Vector mashtabedVector = phycoub::Vector{
        coordinate.x_ / mashtab.x_,
        coordinate.y_ / mashtab.y_,
        coordinate.z_ / mashtab.z_,
    };
    return mashtabedVector;
}

} // namespace phywidgets
