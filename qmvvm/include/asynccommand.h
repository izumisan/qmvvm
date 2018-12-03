#ifndef IZM_QMVVM_ASYNCCOMMAND_H
#define IZM_QMVVM_ASYNCCOMMAND_H

#include <functional>
#include <future>
#include "qmvvm_global.h"
#include "icommand.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT AsyncCommand : public ICommand
{
    Q_OBJECT
Q_SIGNALS:
    void start() const;
    void finished() const;

public:
    AsyncCommand( QObject* parent,
                  const std::function<void()>& execute );
    AsyncCommand( QObject* parent,
                  const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  const bool autoRaise = false );
    virtual ~AsyncCommand() = default;

public Q_SLOTS:
    virtual void execute() override;
public:
    virtual bool canExecute() const override;
    virtual void raiseCanExecuteChanged() const override;
private:
    bool ready() const;
    void setReady( const bool value );

private:
    std::function<void()> m_execute = []{};
    std::function<bool()> m_canExecute = []{return true;};
    std::future<void> m_task = {};
    bool m_ready = false;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_ASYNCCOMMAND_H
