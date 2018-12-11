#include "observablehelper.h"

namespace izm
{
namespace qmvvm
{

#if !defined(IZMQMVVMSHARED_EXPORT)
template class ObservableHelper<bool>;
template class ObservableHelper<unsigned int>;
template class ObservableHelper<int>;
template class ObservableHelper<float>;
template class ObservableHelper<double>;
template class ObservableHelper<QString>;
#endif

} // namespace qmvvm
} // namespace izm
