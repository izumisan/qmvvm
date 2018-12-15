#include <cassert>
#include <future>
#include "commandmanager.h"
#include "asynccommand.h"

namespace izm
{
namespace qmvvm
{

AsyncCommand::AsyncCommand( QObject* parent,
              const std::function<void()>& execute )
    : AsyncCommand( parent, execute, []{return true;}, false )
{
}

AsyncCommand::AsyncCommand( QObject* parent,
              const std::function<void()>& execute,
              const std::function<bool()>& canExecute,
              const bool autoRaise )
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

    connect ( this, &AsyncCommand::finished,
              this, [this] { setReady( true ); },
              Qt::QueuedConnection);

    setReady( true );
}

void AsyncCommand::execute()
{
    if ( ready() )
    {
        setReady( false );
        m_task = std::async( std::launch::async, [this]
        {
            Q_EMIT start();
            m_execute();
            Q_EMIT finished();
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
