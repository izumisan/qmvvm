#include "observablepropertybase.h"

namespace izm
{
namespace qmvvm
{

ObservablePropertyBase::ObservablePropertyBase( QObject* parent )
    : QObject(parent)
{
}

void ObservablePropertyBase::raiseValuePropertyChanged() const
{
    Q_EMIT valuePropertyChanged();
}

} // namespace qmvvm
} // namespace izm
