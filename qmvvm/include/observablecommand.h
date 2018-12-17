#ifndef IZM_QMVVM_OBSERVABLECOMMAND_H
#define IZM_QMVVM_OBSERVABLECOMMAND_H

#include <functional>
#include <QMap>
#include "qmvvm_global.h"
#include "relaycommand.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT ObservableCommand : public RelayCommand
{
    Q_OBJECT
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

public:
    int subscribe( const std::function<void()>& onFinished );
    int subscribe( const std::function<void()>& onStarted, const std::function<void()>& onFinished );
    void unsubscribe( const int& actionid );
    void clear();

private:
    QMap<int, std::function<void()>> m_onStartedActions = {};
    QMap<int, std::function<void()>> m_onFinishedActions = {};
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLECOMMAND_H
