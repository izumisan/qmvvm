#ifndef IZM_QMVVM_ICOMMAND_H
#define IZM_QMVVM_ICOMMAND_H

#include <QObject>

namespace izm
{
namespace qmvvm
{

class ICommand : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool canExecute READ canExecute NOTIFY canExecuteChanged )
Q_SIGNALS:
    void canExecuteChanged() const;

public:
    explicit ICommand( QObject* parent = nullptr ) : QObject(parent) {}
    virtual ~ICommand() = default;

public Q_SLOTS:
    virtual void execute() = 0;
public:
    virtual bool canExecute() const = 0;
    virtual void raiseCanExecuteChanged() const = 0;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_ICOMMAND_H
