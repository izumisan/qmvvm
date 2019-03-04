#ifndef IZM_QMVVM_COMMANDBASE_H
#define IZM_QMVVM_COMMANDBASE_H

#include <QObject>
#include "qmvvm_global.h"

namespace izm
{
namespace qmvvm
{

class ObservablePropertyBase;
class ObservableCollectionBase;

class IZMQMVVMSHARED_EXPORT CommandBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool canExecute READ canExecute NOTIFY canExecuteChanged )
Q_SIGNALS:
    void canExecuteChanged() const;
    void started() const;
    void finished() const;

public:
    explicit CommandBase( QObject* parent );
    virtual ~CommandBase() = default;

public Q_SLOTS:
    virtual void execute() = 0;
public:
    virtual bool canExecute() const = 0;
    virtual void raiseCanExecuteChanged() const;
public:
    void observesProperty( const ObservablePropertyBase* observableProperty ) const;
    void observesCollection( const ObservableCollectionBase* observableCollection ) const;

protected:
    virtual void raiseStarted() const;
    virtual void raiseFinished() const;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COMMANDBASE_H
