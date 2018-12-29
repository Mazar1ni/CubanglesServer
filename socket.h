#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QDebug>
#include <QThreadPool>
#include <QTime>

class Server;
class TcpSocket;
class Room;

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(Server *parent);
    void setSocket(int descriptor);

    Room *getRoom() const;
    void setRoom(Room *value);

    TcpSocket *getSocket() const;

    Server *getParent() const;
    void setParent(Server *value);

    bool getIsPlaying() const;
    void setIsPlaying(bool value);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(QString output);

private:
    TcpSocket* socket;
    Server* parent;
    Room* room;

    bool isPlaying = false;
};

#endif // SOCKET_H
