#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include "viewmodelbase.h"
#include "observableproperty.h"
#include "relaycommand.h"

class MainViewModel : public izm::qmvvm::ViewModelBase
{
    Q_OBJECT
    OBSERVABLE_PROPERTY( value, m_value )
    COMMAND_PROPERTY( command, m_command )
public:
    explicit MainViewModel( QObject* parent = nullptr )
        : izm::qmvvm::ViewModelBase( parent )
        , m_value( izm::qmvvm::ObservableHelper<int>::getter(),
                   izm::qmvvm::ObservableHelper<int>::setter(),
                   parent )
        , m_command( [this]{ qDebug() << m_value.value(); },
                     [this]{ return ( m_value.value() % 3 == 0 ); },
                     parent )
    {
        m_command.observesProperty( &m_value );
    }
    virtual ~MainViewModel() = default;

private:
    izm::qmvvm::ObservableProperty<int> m_value = {};
    izm::qmvvm::RelayCommand m_command = {};
};

#endif // MAINVIEWMODEL_H
