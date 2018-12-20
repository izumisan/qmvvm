#ifndef IZM_QMVVM_OBSERVABLECOLLECTIONBASE_H
#define IZM_QMVVM_OBSERVABLECOLLECTIONBASE_H

#include <QAbstractListModel>
#include "qmvvm_global.h"
#include "collectionchangeargs.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT ObservableCollectionBase : public QAbstractListModel
{
    Q_OBJECT
Q_SIGNALS:
    void collectionChanged( CollectionChangeArgs args ) const;

public:
    explicit ObservableCollectionBase( QObject* parent = nullptr );
    virtual ~ObservableCollectionBase() = default;

public:
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const override = 0;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override = 0;
protected:
    virtual QHash<int, QByteArray> roleNames() const override = 0;

protected:
    virtual void raiseDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles = QVector<int>() );
    virtual void raiseCollectionChanged( const CollectionChangeAction& action, const int index = -1 ) const;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLECOLLECTIONBASE_H
