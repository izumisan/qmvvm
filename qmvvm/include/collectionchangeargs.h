#ifndef IZM_QMVVM_COLLECTIONCHANGEARGS_H
#define IZM_QMVVM_COLLECTIONCHANGEARGS_H

#include "collectionchangeaction.h"

namespace izm
{
namespace qmvvm
{

struct CollectionChangeArgs
{
    CollectionChangeArgs( const CollectionChangeAction& act, const int index = -1 )
        : action( act )
        , target( index )
    {
    }

    CollectionChangeAction action = CollectionChangeAction::Undefined;
    int target = -1;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COLLECTIONCHANGEARGS_H
