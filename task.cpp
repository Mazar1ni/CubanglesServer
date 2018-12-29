#include "task.h"
#include "socket.h"
#include "server.h"
#include "tcpsocket.h"
#include "searchgame.h"
#include "room.h"
#include <QMutex>

Task::Task(QString info, Socket* client) : str(info), client(client)
{

}

Task::~Task()
{
    qDebug() << "task deleted";
}

void Task::sendToClient(QString message)
{
    QMetaObject::invokeMethod(client, "taskResult", Qt::QueuedConnection,
                              Q_ARG(QString, message));
}

void Task::run()
{
    qDebug() << "task started " << str;

    if(str.indexOf("disconnected") != -1)
    {
        if(client->getRoom()!= nullptr)
        {
            client->getRoom()->leaveTheRoom(client);
        }

        client->getParent()->socketList.removeOne(client);

        client->getSocket()->close();
    }
    else if(str.indexOf("~SearchGame~") != -1)
    {
        if(client->getIsPlaying() == false)
        {
            str.remove("~SearchGame~");

            SearchGame::addNewClientInSearch_s(client);
            sendToClient("~SearchGameStarted~");
        }
        else
        {
            sendToClient("~SearchGameNotStarted~");
        }
    }
    else if(str.indexOf("~GameIsLoaded~") != -1)
    {
        if(client->getRoom() != nullptr)
        {
            client->getRoom()->startGame(client);
        }
    }
    else if(str.indexOf("~cource~") != -1)
    {
        if(client->getRoom() != nullptr)
        {
            str.remove("~cource~");

            QStringList list = str.split("!");

            client->getRoom()->nextCource(list[0], list[1], list[2], list[3]);
        }
    }
    else if(str.indexOf("~surrender~") != -1)
    {
        if(client->getRoom() != nullptr)
        {
            client->getRoom()->surrenderGame(client);

            client->setRoom(nullptr);
        }
    }
    else if(str.indexOf("~endgame~") != -1)
    {
        if(client->getRoom() != nullptr)
        {
            client->getRoom()->endGame();

            client->setRoom(nullptr);
        }
    }
    else if(str.indexOf("~version~") != -1)
    {
        str.remove("~version~");

        QStringList list = str.split("!");

        QString versionMajor = list[0];
        QString versionMinor = list[1];

        if(versionMajor.toInt() != ACTUAL_VERSION_MAJOR || versionMinor.toInt() != ACTUAL_VERSION_MINOR)
        {
            sendToClient("~NeedUpdate~");
        }
        else
        {
            sendToClient("~NoUpdate~");
        }
    }
}
