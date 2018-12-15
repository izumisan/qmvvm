#ifndef IZM_QMVVM_COMMANDBASE_H
#define IZM_QMVVM_COMMANDBASE_H

#include <QObject>
#include "qmvvm_global.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT CommandBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool canExecute READ canExecute NOTIFY canExecuteChanged )
Q_SIGNALS:
    void canExecuteChanged() const;
    void started() const;
    void finished() const;

public:
    explicit CommandBase( QObject* parent = nullptr )
        : QObject( parent )
    {
    }
    virtual ~CommandBase() = default;

public Q_SLOTS:
    virtual void execute() = 0;
public:
    virtual bool canExecute() const = 0;

    virtual void raiseCanExecuteChanged() const
    {
        Q_EMIT canExecuteChanged();
    }

    virtual void raiseStarted() const
    {
        Q_EMIT started();
    }

    virtual void raiseFinished() const
    {
        Q_EMIT finished();
    }
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COMMANDBASE_H
