#ifndef IZM_QMVVM_RELAYCOMMAND_H
#define IZM_QMVVM_RELAYCOMMAND_H

#include <functional>
#include "qmvvm_global.h"
#include "commandbase.h"

namespace izm
{
namespace qmvvm
{

class IZMQMVVMSHARED_EXPORT RelayCommand : public CommandBase
{
    Q_OBJECT

public:
    RelayCommand( QObject* parent = nullptr );
    RelayCommand( const std::function<void()>& execute,
                  QObject* parent = nullptr );
    RelayCommand( const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  QObject* parent = nullptr );
    RelayCommand( const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  const bool autoRaise,
                  QObject* parent = nullptr );
    virtual ~RelayCommand() = default;

public Q_SLOTS:
    virtual void execute() override;
public:
    virtual bool canExecute() const override;

private:
    std::function<void()> m_execute = nullptr;
    std::function<bool()> m_canExecute = nullptr;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_RELAYCOMMAND_H
