#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QDebug>
#include "relaycommand.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int value READ value WRITE setValue NOTIFY valueChanged )
    Q_PROPERTY( int count READ count NOTIFY countChanged )
    Q_PROPERTY( izm::qmvvm::RelayCommand* relayCommand READ relayCommand CONSTANT )
signals:
    void valueChanged() const;
    void countChanged() const;

public:
    MainViewModel( QObject* parent = nullptr )
        : QObject(parent)
        , m_relayCommand()
    {
        m_relayCommand = new izm::qmvvm::RelayCommand(
            parent,
            [this]
            {
                setCount( m_count + 1 );
            },
            [this]() -> bool
            {
                bool ret = false;
                if ( m_value != 0 )
                {
                    if ( ( m_value % 3 == 0 ) || ( QString("%1").arg(m_value).contains("3") ) )
                    {
                        ret = true;
                    }
                }
                return ret;
            } );
    }
    virtual ~MainViewModel() = default;

public:
    int value() const
    {
        return m_value;
    }
    void setValue( const int value )
    {
        if ( m_value != value )
        {
            m_value = value;
            emit valueChanged();

            m_relayCommand->raiseCanExecuteChanged();
        }
    }

    int count() const
    {
        return m_count;
    }
    void setCount( const int value )
    {
        if ( m_count != value )
        {
            m_count = value;
            emit countChanged();
        }
    }

    izm::qmvvm::RelayCommand* relayCommand() const
    {
        return m_relayCommand;
    }

private:
    int m_value = 0;
    int m_count = 0;
    izm::qmvvm::RelayCommand* m_relayCommand = nullptr;
};

#endif // MAINVIEWMODEL_H
