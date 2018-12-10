#ifndef IZM_QMVVM_OBSERVABLEHELPER_H
#define IZM_QMVVM_OBSERVABLEHELPER_H

#include <functional>
#include <QVariant>

namespace izm
{
namespace qmvvm
{

template<class T>
class ObservableyHelper
{
public:
    static std::function<QVariant(const T&)> getter()
    {
        return [](const T& data){ return data; };
    }

    static std::function<void(T&, const QVariant&)> setter()
    {
        return [](T& data, const QVariant& value ){ data = value.value<T>(); };
    }
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLEHELPER_H
