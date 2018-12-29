#include "socket.h"
#include "task.h"
#include "tcpsocket.h"
#include <QDataStream>

Socket::Socket(Server *parent) : parent(parent)
{
    socket = new TcpSocket;
}

void Socket::setSocket(int descriptor)
{
    if(socket->setSocketDescriptor(descriptor))
    {
        qDebug() << "socket connected";
    }
    else
    {
        qDebug() << "socket not connected";
    }

    connect(socket, &QTcpSocket::connected, this, &Socket::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Socket::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Socket::readyRead);
}

void Socket::setRoom(Room *value)
{
    room = value;
}

void Socket::connected()
{
    qDebug() << "client connected";
}

void Socket::disconnected()
{
    Task* task = new Task("disconnected", this);
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);

    qDebug() << "client disconnected";
}

void Socket::readyRead()
{
    QByteArray buffer;
    buffer = socket->readAll();

    QDataStream in(buffer);

    QString str;
    in >> str;

    Task* task = new Task(str, this);
    task->setAutoDelete(true);
    connect(task, &Task::result, this, &Socket::taskResult, Qt::DirectConnection);
    QThreadPool::globalInstance()->start(task);
}

void Socket::taskResult(QString output)
{
    qDebug() << "taskResult " << output;
    QByteArray  arrBlock;

    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << output;

    socket->write(arrBlock);
    socket->flush();
}

Room *Socket::getRoom() const
{
    return room;
}

void Socket::setIsPlaying(bool value)
{
    isPlaying = value;
}

bool Socket::getIsPlaying() const
{
    return isPlaying;
}

void Socket::setParent(Server *value)
{
    parent = value;
}

Server *Socket::getParent() const
{
    return parent;
}

TcpSocket *Socket::getSocket() const
{
    return socket;
}
