#include "observablecollection.h"

namespace izm
{
namespace qmvvm
{

#if defined(IZM_QMVVM_BUILT_IN)
template class ObservableCollection<bool>;
template class ObservableCollection<unsigned int>;
template class ObservableCollection<int>;
template class ObservableCollection<float>;
template class ObservableCollection<double>;
template class ObservableCollection<QString>;
#endif

} // namespace qmvvm
} // namespace izm
