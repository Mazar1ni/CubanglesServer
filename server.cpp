#include "server.h"
#include "socket.h"
#include "searchgame.h"
#include "roommanager.h"

Server::Server()
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);

    roomManager = new RoomManager();

    searchGame = new SearchGame(roomManager);
    searchGame->start();
}

void Server::startServer()
{
    if(listen(QHostAddress::Any, 8080))
    {
        qDebug() << "server started";
    }
    else
    {
        qDebug() << "server not started";
    }
}

void Server::incomingConnection(int handle)
{
    qDebug() << "connected";
    Socket * socket = new Socket(this);
    socket->setSocket(handle);

    socketList.append(socket);
}
