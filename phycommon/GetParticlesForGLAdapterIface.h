#ifndef GETPARTICLESFORGLIFACE_H
#define GETPARTICLESFORGLIFACE_H

#include <memory>

#include "ParticleGroup.h"

namespace phywidgets
{

class GetParticlesForGLAdapterIface
{
  public:
    virtual ~GetParticlesForGLAdapterIface() = default;

    virtual phycoub::ParticleGroupList getParticles() const = 0;
};

using GetParticlesForGLAdapterPtr = std::shared_ptr< GetParticlesForGLAdapterIface >;

} // namespace phywidgets

#endif // GETPARTICLESFORGLIFACE_H
