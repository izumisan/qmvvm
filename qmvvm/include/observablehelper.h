#ifndef IZM_QMVVM_OBSERVABLEHELPER_H
#define IZM_QMVVM_OBSERVABLEHELPER_H

#include <functional>
#include <QVariant>

namespace izm
{
namespace qmvvm
{

template<class T>
class ObservableHelper
{
public:
    static std::function<QVariant(const T&)> getter()
    {
        return [](const T& data){ return QVariant( data ); };
    }

    static std::function<void(T&, const QVariant&)> setter()
    {
        return [](T& data, const QVariant& value ){ data = value.value<T>(); };
    }
};

extern template class ObservableHelper<bool>;
extern template class ObservableHelper<unsigned int>;
extern template class ObservableHelper<int>;
extern template class ObservableHelper<float>;
extern template class ObservableHelper<double>;
extern template class ObservableHelper<QString>;

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLEHELPER_H
