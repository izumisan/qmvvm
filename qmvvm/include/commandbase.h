#ifndef IZM_QMVVM_COMMANDBASE_H
#define IZM_QMVVM_COMMANDBASE_H

#include <QObject>

namespace izm
{
namespace qmvvm
{

class CommandBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool canExecute READ canExecute NOTIFY canExecuteChanged )
Q_SIGNALS:
    void canExecuteChanged() const;

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
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COMMANDBASE_H
