#ifndef GETPARTICLESFORGLIFACE_H
#define GETPARTICLESFORGLIFACE_H

#include <memory>

#include "ParticleGroup.h"

namespace phywidgets
{

class GetParticlesAdapterIface
{
  public:
    virtual ~GetParticlesAdapterIface() = default;

    virtual phycoub::ParticleGroupList getParticles() const = 0;
};

using GetParticlesAdapterPtr = std::shared_ptr< GetParticlesAdapterIface >;

} // namespace phywidgets

#endif // GETPARTICLESFORGLIFACE_H