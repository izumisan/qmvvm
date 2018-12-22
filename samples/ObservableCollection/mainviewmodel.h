#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "viewmodelbase.h"
#include "observablecollection.h"


class MainViewModel : public izm::qmvvm::ViewModelBase
{
    Q_OBJECT
    COLLECTION_PROPERTY( collection, m_collection )
public:
    MainViewModel( QObject* parent = nullptr )
        : izm::qmvvm::ViewModelBase( parent )
        , m_collection(
            { 0, 1, 2, 3, 4, 5 },
            {
                izm::qmvvm::CollectionRole<int>(
                    "value",
                    izm::qmvvm::ObservableHelper<int>::getter(),
                    izm::qmvvm::ObservableHelper<int>::setter() )
            },
            parent )
    {
    }
    virtual ~MainViewModel() = default;
private:
    izm::qmvvm::ObservableCollection<int> m_collection = {};
};

#endif // MAINVIEWMODEL_H
