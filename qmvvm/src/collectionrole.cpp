#include "collectionrole.h"

namespace izm
{
namespace qmvvm
{

#if defined(IZM_QMVVM_BUILT_IN)
template class CollectionRole<bool>;
template class CollectionRole<unsigned int>;
template class CollectionRole<int>;
template class CollectionRole<float>;
template class CollectionRole<double>;
template class CollectionRole<QString>;
#endif

} // namespace qmvvm
} // namespace izm
