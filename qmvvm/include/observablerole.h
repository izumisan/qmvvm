#ifndef IZM_QMVVM_OBSERVABLEROLE_H
#define IZM_QMVVM_OBSERVABLEROLE_H

#include <functional>
#include <QVariant>
#include <QString>
#include "qmvvm_global.h"

namespace izm
{
namespace qmvvm
{

template<class T>
class ObservableRole
{
public:
    ObservableRole( const QString& roleName,
                              const std::function<QVariant(const T&)>& getter )
        : ObservableRole( roleName, getter, [](T&, const QVariant&){} )
    {
    }
    ObservableRole( const QString& roleName,
                              const std::function<QVariant(const T&)>& getter,
                              const std::function<void(T&, const QVariant&)>& setter )
        : m_roleName( roleName )
        , m_getter( getter )
        , m_setter( setter )
    {
    }

public:
    QString roleName() const { return m_roleName; }
    std::function<QVariant(const T&)> getter() const { return m_getter; }
    std::function<void(T&, const QVariant&)> setter() const { return m_setter; }

private:
    QString m_roleName = {};
    std::function<QVariant(const T&)> m_getter = nullptr;
    std::function<void(T&, const QVariant&)> m_setter = nullptr;
};

#if !defined(IZM_QMVVM_BUILT_IN)
template class IZMQMVVMSHARED_EXPORT ObservableRole<bool>;
template class IZMQMVVMSHARED_EXPORT ObservableRole<unsigned int>;
template class IZMQMVVMSHARED_EXPORT ObservableRole<int>;
template class IZMQMVVMSHARED_EXPORT ObservableRole<float>;
template class IZMQMVVMSHARED_EXPORT ObservableRole<double>;
template class IZMQMVVMSHARED_EXPORT ObservableRole<QString>;
#else
extern template class ObservableRole<bool>;
extern template class ObservableRole<unsigned int>;
extern template class ObservableRole<int>;
extern template class ObservableRole<float>;
extern template class ObservableRole<double>;
extern template class ObservableRole<QString>;
#endif

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLEROLE_H
