#ifndef IZM_QMVVM_COLLECTIONROLE_H
#define IZM_QMVVM_COLLECTIONROLE_H

#include <functional>
#include <QVariant>
#include <QString>
#include "qmvvm_global.h"

namespace izm
{
namespace qmvvm
{

template<class T>
class CollectionRole
{
public:
    CollectionRole( const QString& roleName,
                    const std::function<QVariant(const T&)>& getter )
        : CollectionRole( roleName, getter, [](T&, const QVariant&){} )
    {
    }
    CollectionRole( const QString& roleName,
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
template class IZMQMVVMSHARED_EXPORT CollectionRole<bool>;
template class IZMQMVVMSHARED_EXPORT CollectionRole<unsigned int>;
template class IZMQMVVMSHARED_EXPORT CollectionRole<int>;
template class IZMQMVVMSHARED_EXPORT CollectionRole<float>;
template class IZMQMVVMSHARED_EXPORT CollectionRole<double>;
template class IZMQMVVMSHARED_EXPORT CollectionRole<QString>;
#else
extern template class CollectionRole<bool>;
extern template class CollectionRole<unsigned int>;
extern template class CollectionRole<int>;
extern template class CollectionRole<float>;
extern template class CollectionRole<double>;
extern template class CollectionRole<QString>;
#endif

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COLLECTIONROLE_H
