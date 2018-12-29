#include "room.h"
#include "socket.h"
#include "roommanager.h"
#include <QDateTime>

Room::Room(Socket *socket1, Socket *socket2)
{
    clients.append(socket1);
    clients.append(socket2);

    socket1->setRoom(this);
    socket2->setRoom(this);

    roomMutex = new QMutex;

    sendToAllClients("~GameFound~");
}

QList<Socket *> Room::getClients()
{
    return clients;
}

void Room::startGame(Socket *socket)
{
    roomMutex->lock();
    if(clients.at(0) == socket)
    {
        client1IsLoaded = true;
    }
    else if(clients.at(1) == socket)
    {
        client2IsLoaded = true;
    }

    if(client1IsLoaded == true && client2IsLoaded == true)
    {
        qsrand(time(0));
        whoTurn = qrand() % 2;

        colorFirst = whoTurn ? "blue" : "gray";
        colorSecond = whoTurn ? "gray" : "blue";

        for(auto it = clients.begin(); it != clients.end(); ++it)
        {
            QMetaObject::invokeMethod(*it, "taskResult", Qt::QueuedConnection,
                                      Q_ARG(QString, "~GameStarted~" + QString::number((clients.at(whoTurn) == *it))));
        }

        QTimer::singleShot(10000, this, &Room::gameIsStarted);
    }
    roomMutex->unlock();
}

void Room::surrenderGame(Socket *socket)
{
    for(auto it = clients.begin(); it != clients.end(); ++it)
    {
        QMetaObject::invokeMethod(*it, "taskResult", Qt::QueuedConnection,
                                  Q_ARG(QString, "~SurrenderGame~" + QString::number((socket == *it))));

        dynamic_cast<Socket*>(*it)->setIsPlaying(false);
    }

    RoomManager::removeRoom_s(this);
    QTimer::singleShot(10000, [=](){
       deleteLater();
    });
}

void Room::endGame()
{
    int whoWon = colorFirst == "gray" ? scoreFirstClient < scoreSecondClient : scoreFirstClient > scoreSecondClient;

    for(auto it = clients.begin(); it != clients.end(); ++it)
    {
        QMetaObject::invokeMethod(*it, "taskResult", Qt::QueuedConnection,
                                  Q_ARG(QString, "~EndGame~" + QString::number((clients.at(whoWon) == *it))));

        dynamic_cast<Socket*>(*it)->setIsPlaying(false);
    }

    RoomManager::removeRoom_s(this);
    QTimer::singleShot(10000, [=](){
       deleteLater();
    });
}

void Room::nextCource(QString row, QString column, QString width, QString height)
{
    //To Do: need check
    sendToAllClients("~NextCource~" + row + "!" + column + "!" + width + "!" + height);

    QThread::msleep(30);

    whoTurn = whoTurn ? 0 : 1;

    if(row.toInt() != -1 && column.toInt() != -1)
    {
        whoTurn ? scoreSecondClient += width.toInt() * height.toInt() : scoreFirstClient += width.toInt() * height.toInt();

        sendToAllClients("~UpdateScore~" + QString::number(scoreFirstClient) + '!' + colorFirst + "!" + QString::number(scoreSecondClient) + "!" + colorSecond);
    }
}

void Room::sendToAllClients(QString message)
{
    for(auto it = clients.begin(); it != clients.end(); ++it)
    {
        QMetaObject::invokeMethod(*it, "taskResult", Qt::QueuedConnection,
                                  Q_ARG(QString, message));
    }
}

void Room::gameIsStarted()
{
    isStarted = true;
}

void Room::leaveTheRoom(Socket *client)
{
    if(isStarted)
    {
        surrenderGame(client);
    }
    else
    {
        for(auto it = clients.begin(); it != clients.end(); ++it)
        {
            dynamic_cast<Socket*>(*it)->setIsPlaying(false);
            QMetaObject::invokeMethod(*it, "taskResult", Qt::QueuedConnection,
                                      Q_ARG(QString, "~LeaveRoom~"));
        }

        RoomManager::removeRoom_s(this);
        QTimer::singleShot(10000, [=](){
           deleteLater();
        });
    }
}
