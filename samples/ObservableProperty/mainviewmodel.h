#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "observableproperty.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( izm::qmvvm::ObservablePropertyBase* ivalue READ ivalue CONSTANT )

public:
    MainViewModel( QObject* parent = nullptr )
        : m_ivalue( izm::qmvvm::ObservableHelper<int>::getter(),
                    izm::qmvvm::ObservableHelper<int>::setter(),
                    parent )
    {
    }
    virtual ~MainViewModel() = default;

public:
    izm::qmvvm::ObservableProperty<int>* ivalue() { return &m_ivalue; }

private:
    izm::qmvvm::ObservableProperty<int> m_ivalue;
};

#endif // MAINVIEWMODEL_H
