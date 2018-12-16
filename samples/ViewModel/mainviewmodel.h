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
        , m_value( izm::qmvvm::ObservableHelper<int>::getter(), parent )
        , m_command( [this]{ commandExecute(); }, parent )
    {
    }
    virtual ~MainViewModel() = default;

public:
    void commandExecute()
    {
        setProperty( m_value, m_value.value() + 1, [this]
        {
            qDebug() << m_value.value();
        } );
    }

private:
    izm::qmvvm::ObservableProperty<int> m_value = {};
    izm::qmvvm::RelayCommand m_command = {};
};

#endif // MAINVIEWMODEL_H
