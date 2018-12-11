#include "observableproperty.h"

namespace izm
{
namespace qmvvm
{

#if defined(IZM_QMVVM_BUILT_IN)
template class ObservableProperty<bool>;
template class ObservableProperty<unsigned int>;
template class ObservableProperty<int>;
template class ObservableProperty<float>;
template class ObservableProperty<double>;
template class ObservableProperty<QString>;
#endif

} // namespace qmvvm
} // namespace izm
