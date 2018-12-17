#include "commandbase.h"

namespace izm
{
namespace qmvvm
{

CommandBase::CommandBase( QObject* parent )
    : QObject( parent )
{
}

void CommandBase::raiseCanExecuteChanged() const
{
    Q_EMIT canExecuteChanged();
}

void CommandBase::raiseStarted() const
{
    Q_EMIT started();
}

void CommandBase::raiseFinished() const
{
    Q_EMIT finished();
}

} // namespace qmvvm
} // namespace izm
