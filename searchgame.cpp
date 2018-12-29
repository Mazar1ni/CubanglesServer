#include "searchgame.h"
#include "socket.h"
#include "roommanager.h"
#include <QMutex>
#include <QTimer>
#include <QTime>
#include <QDebug>

static SearchGame* searchGameInst;

SearchGame::SearchGame(RoomManager *rm) : roomManager(rm)
{
    searchGameInst = this;

    searchGameTimer = new QTimer;
    connect(searchGameTimer, &QTimer::timeout, this, &SearchGame::searchGame);

    mutexClients = new QMutex();
    searchGameTimer->start(5000);
}

void SearchGame::run()
{
    exec();
}

bool SearchGame::addNewClientInSearch_s(Socket *client)
{
    searchGameInst->addNewClientInSearch(client);
}

void SearchGame::addNewClientInSearch(Socket *client)
{
    mutexClients->lock();

    clients.append(client);

    mutexClients->unlock();
}

void SearchGame::searchGame()
{
    mutexClients->lock();

    while(clients.size() >= 2)
    {
        if(roomManager->createRoom(clients.at(0), clients.at(1)))
        {
            clients.removeAt(0);
            clients.removeAt(0);
        }
    }

    mutexClients->unlock();
}
