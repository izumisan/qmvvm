#include <chrono>
#include "commandmanager.h"

namespace izm
{
namespace qmvvm
{

CommandManager * const CommandManager::instance()
{
    static CommandManager singleton;
    return &singleton;
}

CommandManager::~CommandManager()
{
    stop();
}

void CommandManager::timerEvent( QTimerEvent* event )
{
    Q_UNUSED( event );
    Q_EMIT requerySuggested();
}

void CommandManager::start()
{
    if ( m_timerid == 0 )
    {
        m_timerid = startTimer( std::chrono::milliseconds( 50 ) );
    }
}

void CommandManager::stop()
{
    if ( m_timerid != 0 )
    {
        killTimer( m_timerid );
        m_timerid = 0;
    }
}

} // namespace qmvvm
} // namespace izm
