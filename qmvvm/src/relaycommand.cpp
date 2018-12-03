#include <cassert>
#include "commandmanager.h"
#include "relaycommand.h"

namespace izm
{
namespace qmvvm
{

RelayCommand::RelayCommand( QObject* parent,
              const std::function<void()>& execute )
    : RelayCommand( parent, execute, []{return true;}, false )
{
}

RelayCommand::RelayCommand( QObject* parent,
              const std::function<void()>& execute,
              const std::function<bool()>& canExecute,
              const bool autoRaise )
    : ICommand( parent )
    , m_execute( execute )
    , m_canExecute( canExecute )
{
    assert( m_execute != nullptr );
    assert( m_canExecute != nullptr );

    if ( autoRaise )
    {
        connect( CommandManager::instance(),
                 &CommandManager::requerySuggested,
                 this,
                 [this] { raiseCanExecuteChanged(); },
                 Qt::QueuedConnection );

        CommandManager::instance()->start();
    }
}

void RelayCommand::execute()
{
    m_execute();
}

bool RelayCommand::canExecute() const
{
    return m_canExecute();
}

void RelayCommand::raiseCanExecuteChanged() const
{
    Q_EMIT canExecuteChanged();
}

} // namespace qmvvm
} // namespace izm
