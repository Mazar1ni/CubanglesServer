#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Socket;
class RoomManager;
class SearchGame;

class Server : public QTcpServer
{
public:
    Server();
    void startServer();

protected:
    void incomingConnection(int handle);

public:
    QList<Socket*> socketList;

    RoomManager* roomManager;
    SearchGame* searchGame;
};

#endif // SERVER_H
