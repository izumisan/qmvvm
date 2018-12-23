#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "viewmodelbase.h"
#include "observablecollection.h"
#include "foo.h"

class MainViewModel : public izm::qmvvm::ViewModelBase
{
    Q_OBJECT
    COLLECTION_PROPERTY( collection, m_collection )
    COLLECTION_PROPERTY( foos, *m_foos )
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
        , m_foos()
    {
        auto&& foos = QList<Foo>
        {
            Foo("foo0", 0), Foo("foo1", 1), Foo("foo2", 2),
            Foo("foo3", 3), Foo("foo4", 4), Foo("foo5", 5)
        };
        auto&& roles = QList<izm::qmvvm::CollectionRole<Foo>>
        {
            izm::qmvvm::CollectionRole<Foo>(
                "name",
                [](const Foo& foo){ return foo.name(); } ),
            izm::qmvvm::CollectionRole<Foo>(
                "value",
                [](const Foo& foo){ return foo.value(); },
                [](Foo& foo, const QVariant& value){ foo.setValue( value.toInt() ); } )
        };
        m_foos = new izm::qmvvm::ObservableCollection<Foo>( foos, roles, parent );
    }
    virtual ~MainViewModel() = default;
private:
    izm::qmvvm::ObservableCollection<int> m_collection = {};
    izm::qmvvm::ObservableCollection<Foo>* m_foos = nullptr;
};

#endif // MAINVIEWMODEL_H
