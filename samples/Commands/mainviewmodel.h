#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "relaycommand.h"
#include "asynccommand.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int value READ value WRITE setValue NOTIFY valueChanged )
    Q_PROPERTY( QString message READ message WRITE setMessage NOTIFY messageChanged )
    Q_PROPERTY( izm::qmvvm::RelayCommand* relayCommand1 READ relayCommand1 CONSTANT )
    Q_PROPERTY( izm::qmvvm::RelayCommand* relayCommand2 READ relayCommand2 CONSTANT )
    Q_PROPERTY( izm::qmvvm::AsyncCommand* asyncCommand1 READ asyncCommand1 CONSTANT )
    Q_PROPERTY( izm::qmvvm::AsyncCommand* asyncCommand2 READ asyncCommand2 CONSTANT )

signals:
    void valueChanged() const;
    void messageChanged() const;
    void started() const;
    void completed() const;

public:
    explicit MainViewModel( QObject* parent = nullptr );
    virtual ~MainViewModel() = default;

public:
    int value() const { return m_value; }
    void setValue( const int value )
    {
        if ( m_value != value )
        {
            m_value = value;
            emit valueChanged();

            emit m_relayCommand1->raiseCanExecuteChanged();
            emit m_asyncCommand1->raiseCanExecuteChanged();
        }
    }
    QString message() const { return m_message; }
    void setMessage( const QString& message )
    {
        if ( m_message != message )
        {
            m_message = message;
            emit messageChanged();
        }
    }

    izm::qmvvm::RelayCommand* relayCommand1() const { return m_relayCommand1; }
    izm::qmvvm::RelayCommand* relayCommand2() const { return m_relayCommand2; }
    izm::qmvvm::AsyncCommand* asyncCommand1() const { return m_asyncCommand1; }
    izm::qmvvm::AsyncCommand* asyncCommand2() const { return m_asyncCommand2; }

public:
    void commandExecute();
    bool canCommandExecute() const;

private:
    int m_value = 0;
    QString m_message = "";
    izm::qmvvm::RelayCommand* m_relayCommand1;
    izm::qmvvm::RelayCommand* m_relayCommand2;
    izm::qmvvm::AsyncCommand* m_asyncCommand1;
    izm::qmvvm::AsyncCommand* m_asyncCommand2;
};

#endif // MAINVIEWMODEL_H
