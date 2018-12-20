#include "observablerole.h"

namespace izm
{
namespace qmvvm
{

#if defined(IZM_QMVVM_BUILT_IN)
template class ObservableRole<bool>;
template class ObservableRole<unsigned int>;
template class ObservableRole<int>;
template class ObservableRole<float>;
template class ObservableRole<double>;
template class ObservableRole<QString>;
#endif

} // namespace qmvvm
} // namespace izm
