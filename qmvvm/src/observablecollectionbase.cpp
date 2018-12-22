#include "observablecollectionbase.h"

namespace izm
{
namespace qmvvm
{

ObservableCollectionBase::ObservableCollectionBase( QObject* parent )
    : QAbstractListModel( parent )
{
}

void ObservableCollectionBase::raiseDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles )
{
    Q_EMIT dataChanged( topLeft, bottomRight, roles );
}

void ObservableCollectionBase::raiseCollectionChanged( const CollectionChangeAction& action, const int index ) const
{
    Q_EMIT collectionChanged( CollectionChangeArgs( action, index ) );
}

} // namespace qmvvm
} // namespace izm
