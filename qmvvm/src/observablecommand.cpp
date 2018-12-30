#include <cassert>
#include "commandmanager.h"
#include "observablecommand.h"

namespace izm
{
namespace qmvvm
{

ObservableCommand::ObservableCommand( QObject* parent )
    : ObservableCommand( []{}, []{return true;}, false, parent )
{
}

ObservableCommand::ObservableCommand( const std::function<void()>& execute,
                                      QObject* parent )
    : ObservableCommand( execute, []{return true;}, false, parent )
{
}

ObservableCommand::ObservableCommand( const std::function<void()>& execute,
                                      const std::function<bool()>& canExecute,
                                      QObject* parent )
    : ObservableCommand( execute, canExecute, false, parent )
{
}

ObservableCommand::ObservableCommand( const std::function<void()>& execute,
                                      const std::function<bool()>& canExecute,
                                      const bool autoRaise,
                                      QObject* parent )
    : CommandBase( parent )
    , m_execute( execute )
    , m_canExecute( canExecute )
{
    assert( m_execute != nullptr );
    assert( m_canExecute != nullptr );

    if ( autoRaise )
    {
        CommandManager::instance()->registerCommand( this );
    }

    connect( this, &ObservableCommand::started,
             this, [this] { setReady( false ); },
             Qt::DirectConnection );

    connect( this, &ObservableCommand::finished,
             this, [this] { setReady( true ); },
             Qt::QueuedConnection );

    connect ( this, &ObservableCommand::asyncFinished,
              this, [this] { raiseFinished(); },
              Qt::QueuedConnection );

    connect( this, &ObservableCommand::started,
             this, [this]
    {
        for ( auto&& action : m_onStartedActions.values() )
        {
            if ( action )
            {
                action();
            }
        }
    } );

    connect( this, &ObservableCommand::finished,
             this, [this]
    {
        for ( auto&& action : m_onFinishedActions.values() )
        {
            if ( action )
            {
                action();
            }
        }
    } );

    setReady( true );
}

void ObservableCommand::execute()
{
    if ( !m_isAsync )
    {
        executeDirect();
    }
    else
    {
        executeAsync();
    }
}

bool ObservableCommand::canExecute() const
{
    return m_ready ? m_canExecute() : false;
}

bool ObservableCommand::isAsync() const
{
    return m_isAsync;
}

void ObservableCommand::setAsync( const bool value )
{
    m_isAsync = value;
}

int ObservableCommand::subscribe( const std::function<void()>& onFinished )
{
    return subscribe( nullptr, onFinished );
}

int ObservableCommand::subscribe( const std::function<void()>& onStarted,
                                  const std::function<void()>& onFinished )
{
    constexpr int invalidIndex = -1;
    static int actionid = 0;

    int ret = invalidIndex;

    if ( ( onStarted != nullptr ) || ( m_onStartedActions.contains( actionid ) != true ) )
    {
        m_onStartedActions.insert( actionid, onStarted );
        ret = actionid;
    }

    if ( ( onFinished != nullptr ) || ( m_onFinishedActions.contains( actionid ) != true ) )
    {
        m_onFinishedActions.insert( actionid, onFinished );
        ret = actionid;
    }

    if ( ret != invalidIndex )
    {
        ++actionid;
    }
    return ret;
}

void ObservableCommand::unsubscribe( const int& actionid )
{
    if ( m_onStartedActions.contains( actionid ) )
    {
        m_onStartedActions.remove( actionid );
    }

    if ( m_onFinishedActions.contains( actionid ) )
    {
        m_onFinishedActions.remove( actionid );
    }
}

void ObservableCommand::clear()
{
    m_onStartedActions.clear();
    m_onFinishedActions.clear();
}

void ObservableCommand::executeDirect()
{
    raiseStarted();
    m_execute();
    raiseFinished();
}

void ObservableCommand::executeAsync()
{
    if ( m_ready )
    {
        raiseStarted();
        m_task = std::async( std::launch::async, [this]
        {
            Q_EMIT asyncStarted();
            m_execute();
            Q_EMIT asyncFinished();
        } );
    }
}

void ObservableCommand::setReady( const bool value )
{
    if ( m_ready != value )
    {
        m_ready = value;
        raiseCanExecuteChanged();
    }
}

} // namespace qmvvm
} // namespace izm
