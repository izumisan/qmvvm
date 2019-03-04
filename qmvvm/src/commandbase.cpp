#include "observablepropertybase.h"
#include "observablecollectionbase.h"
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

void CommandBase::observesProperty( const ObservablePropertyBase* observableProperty ) const
{
    connect( observableProperty,
             &ObservablePropertyBase::valuePropertyChanged,
             this,
             [this]{ raiseCanExecuteChanged(); } );
}

void CommandBase::observesCollection( const ObservableCollectionBase* observableCollection ) const
{
    connect( observableCollection,
             &ObservableCollectionBase::collectionChanged,
             this,
             [this]{ raiseCanExecuteChanged(); } );
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
