#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include "viewmodelbase.h"
#include "observablecommand.h"
#include "observableproperty.h"

class MainViewModel : public izm::qmvvm::ViewModelBase
{
    Q_OBJECT
    COMMAND_PROPERTY( command, m_command )
    OBSERVABLE_PROPERTY( value, m_value )
public:
    explicit MainViewModel( QObject* parent = nullptr )
        : izm::qmvvm::ViewModelBase( parent )
        , m_command( [this]{ commandExecute(); }, parent )
        , m_value( izm::qmvvm::ObservableHelper<int>::getter(), parent )
    {
        m_command.subscribe( []{ qDebug() << "onStarted"; },
                             []{ qDebug() << "onFinished"; } );
    }
    virtual ~MainViewModel() = default;

public:
    void commandExecute()
    {
        setProperty( m_value, m_value.value() + 1, [this]
        {
            qDebug() << "onChanged" << m_value.value();
        } );
    }

private:
    izm::qmvvm::ObservableCommand m_command = {};
    izm::qmvvm::ObservableProperty<int> m_value = {};
};

#endif // MAINVIEWMODEL_H
