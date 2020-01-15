#ifndef ADDPARTICLECONTROLLERADAPTERIFACE_H
#define ADDPARTICLECONTROLLERADAPTERIFACE_H

#include <memory>

#include "Vector.h"
#include "Particle.h"

namespace phywidgets
{

using namespace phycoub;

class AddParticleControllerAdapterIface
{
  public:
    virtual ~AddParticleControllerAdapterIface() = default;

    virtual void addParticle( const Vector& coordinate, const Vector& speed,
        const ParticleOptions& particleOptions );
};

using AddParticleControllerAdapterPtr
    = std::shared_ptr< AddParticleControllerAdapterIface >;

} // namespace phywidgets

#endif // ADDPARTICLECONTROLLERADAPTERIFACE_H
