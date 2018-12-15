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
    RelayCommand( QObject* parent,
                  const std::function<void()>& execute );
    RelayCommand( QObject* parent,
                  const std::function<void()>& execute,
                  const std::function<bool()>& canExecute,
                  const bool autoRaise = false );
    virtual ~RelayCommand() = default;

public Q_SLOTS:
    virtual void execute() override;
public:
    virtual bool canExecute() const override;

private:
    std::function<void()> m_execute = []{};
    std::function<bool()> m_canExecute = []{return true;};
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_RELAYCOMMAND_H
