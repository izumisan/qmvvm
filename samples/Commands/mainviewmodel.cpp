#include <thread>
#include <chrono>
#include <QDebug>
#include "mainviewmodel.h"


MainViewModel::MainViewModel( QObject* parent )
    : QObject(parent)
{
    m_relayCommand1 = new izm::qmvvm::RelayCommand(
                parent,
                [this] { commandExecute(); },
                [this] { return canCommandExecute(); } );

    m_relayCommand2 = new izm::qmvvm::RelayCommand(
                parent,
                [this] { commandExecute(); },
                [this] { return canCommandExecute(); },
                true );

    m_asyncCommand1 = new izm::qmvvm::AsyncCommand(
                parent,
                [this] { commandExecute(); },
                [this] { return canCommandExecute(); } );

    m_asyncCommand2 = new izm::qmvvm::AsyncCommand(
                parent,
                [this] { commandExecute(); },
                [this] { return canCommandExecute(); },
                true );
}

void MainViewModel::commandExecute()
{
    qDebug() << "start...";
    emit started();

    setMessage( "3" );
    std::this_thread::sleep_for( std::chrono::seconds(1) );
    setMessage( "2" );
    std::this_thread::sleep_for( std::chrono::seconds(1) );
    setMessage( "1" );
    std::this_thread::sleep_for( std::chrono::seconds(1) );

    setMessage( "" );

    emit completed();
    qDebug() << "end";
}

bool MainViewModel::canCommandExecute() const
{
    bool ret = false;
    if ( m_value != 0 )
    {
        if ( m_value % 3 == 0 )
        {
            ret = true;
        }
        else if ( QString("%1").arg( m_value ).contains( "3" ) )
        {
            ret = true;
        }
        else
        {
        }
    }
    return ret;
}
