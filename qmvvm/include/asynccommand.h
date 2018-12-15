#ifndef IZM_QMVVM_ASYNCCOMMAND_H
#define IZM_QMVVM_ASYNCCOMMAND_H

#include <functional>
#include <future>
#include "qmvvm_global.h"
#include "commandbase.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT AsyncCommand : public CommandBase
{
    Q_OBJECT
Q_SIGNALS:
    void asyncStarted() const;
    void asyncFinished() const;

public:
    AsyncCommand( QObject* parent = nullptr );
    AsyncCommand( const std::function<void()>& execute,
                  QObject* parent = nullptr );
    AsyncCommand( const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  QObject* parent = nullptr );
    AsyncCommand( const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  const bool autoRaise,
                  QObject* parent = nullptr );
    virtual ~AsyncCommand() = default;

public Q_SLOTS:
    virtual void execute() override;
public:
    virtual bool canExecute() const override;
private:
    bool ready() const;
    void setReady( const bool value );

private:
    std::function<void()> m_execute = nullptr;
    std::function<bool()> m_canExecute = nullptr;
    std::future<void> m_task = {};
    bool m_ready = false;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_ASYNCCOMMAND_H
