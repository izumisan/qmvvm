#ifndef IZM_QMVVM_VIWEMODELBASE_H
#define IZM_QMVVM_VIWEMODELBASE_H

#include <functional>
#include <QObject>
#include "qmvvm_global.h"
#include "observableproperty.h"

#define OBSERVABLE_PROPERTY( name, var ) \
    Q_PROPERTY( izm::qmvvm::ObservablePropertyBase* name READ get_##name CONSTANT ) \
    izm::qmvvm::ObservablePropertyBase* get_##name() { return &( var ); }

#define COLLECTION_PROPERTY( name, var ) \
    Q_PROPERTY( izm::qmvvm::ObservableCollectionBase* name READ get_##name CONSTANT ) \
    izm::qmvvm::ObservableCollectionBase* get_##name() { return &( var ); }

#define COMMAND_PROPERTY( name, var ) \
    Q_PROPERTY( izm::qmvvm::CommandBase* name READ get_##name CONSTANT ) \
    izm::qmvvm::CommandBase* get_##name() { return &( var ); }

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT ViewModelBase : public QObject
{
    Q_OBJECT
public:
    explicit ViewModelBase( QObject* parent = nullptr );
    virtual ~ViewModelBase() = default;

    template<class T>
    bool setProperty( ObservableProperty<T>& property,
                      const T& value,
                      const std::function<void()>& onChanged = nullptr )
    {
        bool ret = false;
        auto&& saved = property.value();
        property.setValue( value );
        if ( saved != property.value() )
        {
            ret = true;
            if ( onChanged )
            {
                onChanged();
            }
        }
        return ret;
    }
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_VIWEMODELBASE_H
