#ifndef IZM_QMVVM_COMMANDMANAGER_H
#define IZM_QMVVM_COMMANDMANAGER_H

#include <QObject>

namespace izm
{
namespace qmvvm
{

class CommandManager : public QObject
{
    Q_OBJECT
Q_SIGNALS:
    void requerySuggested() const;

public:
    static CommandManager * const instance();

private:
    CommandManager() = default;
public:
    virtual ~CommandManager();
private:
    CommandManager( const CommandManager& ) = delete;
    CommandManager& operator = ( const CommandManager& ) = delete;

protected:
    void timerEvent( QTimerEvent* event );

public:
    void start();
    void stop();

private:
    int m_timerid = 0;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_COMMANDMANAGER_H
