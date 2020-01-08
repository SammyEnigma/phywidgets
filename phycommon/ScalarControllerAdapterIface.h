#ifndef SCALARVALUECONTROLLERADAPTERIFACE_H
#define SCALARVALUECONTROLLERADAPTERIFACE_H

#include <memory>

namespace phywidgets
{

template< typename ValueType >
class ScalarControllerAdapterIface
{
  public:
    virtual ~ScalarControllerAdapterIface() = default;

    virtual ValueType getValue() const = 0;
    virtual void setValue( ValueType value ) = 0;
};

using ScalarDoubleControllerAdapterPtr
    = std::shared_ptr< ScalarControllerAdapterIface< double > >;

using ScalarLongControllerAdapterPtr
    = std::shared_ptr< ScalarControllerAdapterIface< long > >;

template< typename ValueType, typename Type, ValueType ( Type::*getValueMethod )() const,
    void ( Type::*setValueMethod )( ValueType ) >
class ScalarControllerAdapter : public ScalarControllerAdapterIface< ValueType >
{
  public:
    using TypePtr = std::shared_ptr< Type >;

    ScalarControllerAdapter( TypePtr coub );
    virtual ~ScalarControllerAdapter() override = default;

    // Implementation of ScalarDoubleControllerAdapterIface
    virtual ValueType getValue() const override;
    virtual void setValue( ValueType value ) override;

  private:
    TypePtr coub_ = nullptr;
};

template< typename ValueType, typename Type, ValueType ( Type::*getValueMethod )() const,
    void ( Type::*setValueMethod )( ValueType ) >
ScalarControllerAdapter< ValueType, Type, getValueMethod,
    setValueMethod >::ScalarControllerAdapter( TypePtr coub )
    : coub_( coub )
{
}

// virtual override
template< typename ValueType, typename Type, ValueType ( Type::*getValueMethod )() const,
    void ( Type::*setValueMethod )( ValueType ) >
ValueType
ScalarControllerAdapter< ValueType, Type, getValueMethod, setValueMethod >::getValue()
    const
{
    double value = 0.;
    if ( coub_ )
    {
        value = ( ( *coub_ ).*getValueMethod )();
    }
    return value;
}

// virtual override
template< typename ValueType, typename Type, ValueType ( Type::*getValueMethod )() const,
    void ( Type::*setValueMethod )( ValueType ) >
void ScalarControllerAdapter< ValueType, Type, getValueMethod, setValueMethod >::setValue(
    ValueType value )
{
    if ( coub_ )
    {
        ( ( *coub_ ).*setValueMethod )( value );
    }
}

} // namespace phywidgets

#endif // SCALARVALUECONTROLLERADAPTERIFACE_H
