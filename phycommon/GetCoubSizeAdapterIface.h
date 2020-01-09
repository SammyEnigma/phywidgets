#ifndef GETCOUBSIZEADAPTERIFACE_H
#define GETCOUBSIZEADAPTERIFACE_H

#include <memory>

#include "Vector.h"

namespace phywidgets
{

class GetCoubSizeAdapterIface
{
  public:
    virtual ~GetCoubSizeAdapterIface() = default;

    virtual phycoub::Vector getCoubSize() const = 0;
};

using GetCoubSizeAdapterPtr = std::shared_ptr< GetCoubSizeAdapterIface >;

} // namespace phywidgets

#endif // GETCOUBSIZEADAPTERIFACE_H
