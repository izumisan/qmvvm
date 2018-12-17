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
    : RelayCommand( execute, canExecute, autoRaise, parent )
{
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

} // namespace qmvvm
} // namespace izm
