#include <cassert>
#include <future>
#include "commandmanager.h"
#include "asynccommand.h"

namespace izm
{
namespace qmvvm
{

AsyncCommand::AsyncCommand( QObject* parent )
    : AsyncCommand( []{}, []{return true;}, false, parent )
{
}

AsyncCommand::AsyncCommand( const std::function<void()>& execute,
                            QObject* parent )
    : AsyncCommand( execute, []{return true;}, false, parent )
{
}

AsyncCommand::AsyncCommand( const std::function<void()>& execute,
                            const std::function<bool()>& canExecute,
                            QObject* parent )
    : AsyncCommand( execute, canExecute, false, parent )
{
}

AsyncCommand::AsyncCommand( const std::function<void()>& execute,
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

    connect ( this, &AsyncCommand::asyncFinished,
              this, [this]
              {
                  setReady( true );
                  raiseFinished();
              },
              Qt::QueuedConnection );

    setReady( true );
}

void AsyncCommand::execute()
{
    if ( ready() )
    {
        setReady( false );
        raiseStarted();
        m_task = std::async( std::launch::async, [this]
        {
            Q_EMIT asyncStarted();
            m_execute();
            Q_EMIT asyncFinished();
        } );
    }
}

bool AsyncCommand::canExecute() const
{
    return ready() ? m_canExecute() : false;
}

bool AsyncCommand::ready() const
{
    return m_ready;
}

void AsyncCommand::setReady( const bool value )
{
    if ( m_ready != value )
    {
        m_ready = value;
        raiseCanExecuteChanged();
    }
}

} // namespace qmvvm
} // namespace izm
