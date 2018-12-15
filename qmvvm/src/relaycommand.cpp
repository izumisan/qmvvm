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
}

void RelayCommand::execute()
{
    m_execute();
}

bool RelayCommand::canExecute() const
{
    return m_canExecute();
}

} // namespace qmvvm
} // namespace izm
