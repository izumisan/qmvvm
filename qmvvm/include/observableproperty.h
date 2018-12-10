#ifndef IZM_QMVVM_OBSERVABLEPROPERTY_H
#define IZM_QMVVM_OBSERVABLEPROPERTY_H

#include <functional>
#include <QMap>
#include "qmvvm_global.h"
#include "observablepropertybase.h"
#include "observablehelper.h"

namespace izm
{
namespace qmvvm
{

template<class T>
class ObservableProperty : public ObservablePropertyBase
{
public:
    ObservableProperty( const std::function<QVariant(const T&)>& getter,
                        QObject* parent = nullptr )
        : ObservableProperty( {}, getter, [](T&, const QVariant&){}, parent )
    {
    }
    ObservableProperty( const std::function<QVariant(const T&)>& getter,
                        const std::function<void(T&, const QVariant&)>& setter,
                        QObject* parent = nullptr )
        : ObservableProperty( {}, getter, setter, parent )
    {
    }
    ObservableProperty( const T& value,
                        const std::function<QVariant(const T&)>& getter,
                        QObject* parent = nullptr )
        : ObservableProperty( value, getter, [](T&, const QVariant&){}, parent )
    {
    }
    ObservableProperty( const T& value,
                        const std::function<QVariant(const T&)>& getter,
                        const std::function<void(T&, const QVariant&)>& setter,
                        QObject* parent = nullptr )
        : ObservablePropertyBase( parent )
        , m_value( value )
        , m_getter( getter )
        , m_setter( setter )
    {
        assert( getter != nullptr );
        assert( setter != nullptr );
    }
    virtual ~ObservableProperty() = default;

protected:
    virtual QVariant valueProperty() const override
    {
        return m_getter( m_value );
    }

    virtual void setValueProperty( const QVariant& value ) override
    {
        if ( valueProperty() != value )
        {
            m_setter( m_value, value );
            raiseValuePropertyChanged();
        }
    }

public:
    virtual void raiseValuePropertyChanged() const override
    {
        ObservablePropertyBase::raiseValuePropertyChanged();

        for ( auto&& action : m_actions )
        {
            if ( action != nullptr )
            {
                action( m_value );
            }
        }
    }

public:
    T value() const
    {
        return m_value;
    }

    bool setValue( const T& data, bool doesRaisePropertyChanged = true )
    {
        bool ret = false;
        if ( m_value != data )
        {
            m_value = data;
            ret = true;

            if ( doesRaisePropertyChanged )
            {
                raiseValuePropertyChanged();
            }
        }
        return ret;
    }

    int subscribe( const std::function<void(const T&)>& action )
    {
        constexpr int invalidIndex = -1;
        static int actionid = 0;

        int ret = invalidIndex;
        if ( !m_actions.contains( actionid ) )
        {
            ret = actionid;
            m_actions.insert( actionid++, action );
        }
        return ret;
    }

    void unsubscribe( const int& actionid )
    {
        if ( m_actions.contains( actionid ) )
        {
            m_actions.remove( actionid );
        }
    }

    void clear()
    {
        m_actions.clear();
    }

private:
    T m_value = {};
    std::function<QVariant(const T&)> m_getter = nullptr;
    std::function<void(T&, const QVariant&)> m_setter = nullptr;
    QMap<int, std::function<void(const T&)>> m_actions = {};
};

#if defined(IZMQMVVMSHARED_EXPORT)
template class IZMQMVVMSHARED_EXPORT ObservableProperty<bool>;
template class IZMQMVVMSHARED_EXPORT ObservableProperty<unsigned int>;
template class IZMQMVVMSHARED_EXPORT ObservableProperty<int>;
template class IZMQMVVMSHARED_EXPORT ObservableProperty<float>;
template class IZMQMVVMSHARED_EXPORT ObservableProperty<double>;
template class IZMQMVVMSHARED_EXPORT ObservableProperty<QString>;
#else
extern template class ObservableProperty<bool>;
extern template class ObservableProperty<unsigned int>;
extern template class ObservableProperty<int>;
extern template class ObservableProperty<float>;
extern template class ObservableProperty<double>;
extern template class ObservableProperty<QString>;
#endif

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLEPROPERTY_H
