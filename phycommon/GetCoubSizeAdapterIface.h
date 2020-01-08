#ifndef GETCOUBSIZEADAPTERIFACE_H
#define GETCOUBSIZEADAPTERIFACE_H

#include <memory>

namespace phywidgets
{

class GetCoubSizeAdapterIface
{
  public:
    virtual ~GetCoubSizeAdapterIface() = default;

    virtual double getCoubSize() = 0;
};

using GetCoubSizeAdapterPtr = std::shared_ptr< GetCoubSizeAdapterIface >;

} // namespace phywidgets

#endif // GETCOUBSIZEADAPTERIFACE_H
