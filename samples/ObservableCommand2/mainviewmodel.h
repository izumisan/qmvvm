#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <thread>
#include <chrono>
#include <QObject>
#include <QDebug>
#include "viewmodelbase.h"
#include "observablecommand.h"
#include "observableproperty.h"

class MainViewModel : public izm::qmvvm::ViewModelBase
{
    Q_OBJECT
    OBSERVABLE_PROPERTY( value, m_value )
    COMMAND_PROPERTY( command1, m_command1 )
    COMMAND_PROPERTY( command2, m_command2 )

public:
    explicit MainViewModel( QObject* parent = nullptr )
        : izm::qmvvm::ViewModelBase( parent )
        , m_value( izm::qmvvm::ObservableHelper<int>::getter(), parent )
        , m_command1( [this]{ commandExecute(); }, parent )
        , m_command2( [this]{ commandExecute(); }, parent )
    {
        m_command1.subscribe( []{ qDebug() << "onStarted"; },
                              []{ qDebug() << "onFinished"; } );
        m_command2.subscribe( []{ qDebug() << "onStarted"; },
                              []{ qDebug() << "onFinished"; } );
        m_command2.setAsync( true );
    }
    virtual ~MainViewModel() = default;

public:
    void commandExecute()
    {
        std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
        setProperty( m_value, m_value.value() + 1 );
    }

private:
    izm::qmvvm::ObservableProperty<int> m_value = {};
    izm::qmvvm::ObservableCommand m_command1 = {};
    izm::qmvvm::ObservableCommand m_command2 = {};
};

#endif // MAINVIEWMODEL_H
