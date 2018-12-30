#ifndef IZM_QMVVM_OBSERVABLECOMMAND_H
#define IZM_QMVVM_OBSERVABLECOMMAND_H

#include <functional>
#include <future>
#include <QMap>
#include "qmvvm_global.h"
#include "commandbase.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT ObservableCommand : public CommandBase
{
    Q_OBJECT
    Q_PROPERTY( bool asyncEnabled READ asyncEnabled WRITE setAsyncEnabled NOTIFY asyncEnabledChanged )
Q_SIGNALS:
    void asyncEnabledChanged() const;
    void asyncStarted() const;
    void asyncFinished() const;

public:
    ObservableCommand( QObject* parent = nullptr );
    ObservableCommand( const std::function<void()>& execute,
                       QObject* parent = nullptr );
    ObservableCommand( const std::function<void()>& execute,
                       const std::function<bool()>& canExecute,
                       QObject* parent = nullptr );
    ObservableCommand( const std::function<void()>& execute,
                       const std::function<bool()>& canExecute,
                       const bool autoRaise,
                       QObject* parent = nullptr );
    virtual ~ObservableCommand() = default;

public Q_SLOTS:
    virtual void execute() override;
public:
    virtual bool canExecute() const override;

public:
    bool asyncEnabled() const;
    void setAsyncEnabled( const bool value );
    int subscribe( const std::function<void()>& onFinished );
    int subscribe( const std::function<void()>& onStarted, const std::function<void()>& onFinished );
    void unsubscribe( const int& actionid );
    void clear();

private:
    void executeDirect();
    void executeAsync();
    void setReady( const bool value );

private:
    std::function<void()> m_execute = nullptr;
    std::function<bool()> m_canExecute = nullptr;
    bool m_asyncEnabled = false;
    bool m_ready = false;
    std::future<void> m_task = {};
    QMap<int, std::function<void()>> m_onStartedActions = {};
    QMap<int, std::function<void()>> m_onFinishedActions = {};
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLECOMMAND_H
