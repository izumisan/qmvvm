#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <memory>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include "observableproperty.h"
#include "foo.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( izm::qmvvm::ObservablePropertyBase* ivalue READ ivalue CONSTANT )
    Q_PROPERTY( izm::qmvvm::ObservablePropertyBase* fooName READ fooName CONSTANT )
    Q_PROPERTY( izm::qmvvm::ObservablePropertyBase* fooValue READ fooValue CONSTANT )

public:
    MainViewModel( QObject* parent = nullptr )
        : m_ivalue( izm::qmvvm::ObservableHelper<int>::getter(),
                    izm::qmvvm::ObservableHelper<int>::setter(),
                    parent )
        , m_fooName( [](const std::shared_ptr<Foo>& data) { return data->name(); },
                     [](std::shared_ptr<Foo>& data, const QVariant& value) { data->setName( value.toString() ); } )
        , m_fooValue( [](const std::shared_ptr<Foo>& data) { return data->value(); },
                      [](std::shared_ptr<Foo>& data, const QVariant& value) { data->setValue( value.toInt() ); } )
    {
        m_fooName.setValue( m_foo );
        m_fooValue.setValue( m_foo );
    }
    virtual ~MainViewModel() = default;

public:
    izm::qmvvm::ObservableProperty<int>* ivalue() { return &m_ivalue; }
    izm::qmvvm::ObservableProperty<std::shared_ptr<Foo>>* fooName() { return &m_fooName; }
    izm::qmvvm::ObservableProperty<std::shared_ptr<Foo>>* fooValue() { return &m_fooValue; }

public slots:
    void printFooValue() const
    {
        qDebug() << m_foo->name() << m_foo->value();
    }

private:
    izm::qmvvm::ObservableProperty<int> m_ivalue;
    izm::qmvvm::ObservableProperty<std::shared_ptr<Foo>> m_fooName = nullptr;
    izm::qmvvm::ObservableProperty<std::shared_ptr<Foo>> m_fooValue = nullptr;

    std::shared_ptr<Foo> m_foo = std::make_shared<Foo>( "foo", 0 );
};

#endif // MAINVIEWMODEL_H
