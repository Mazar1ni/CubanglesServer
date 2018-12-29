#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QTimer>
#include <QMutex>

class Socket;

struct GameInfo
{
    GameInfo(QString name) : nameUser(name){}

    QString nameUser;
    int score = 0;
};

class Room : public QObject
{
    Q_OBJECT
public:
    Room(Socket *socket1, Socket* socket2);

    void leaveTheRoom(Socket *client);
    QList<Socket *> getClients();
    void startGame(Socket* socket);
    void surrenderGame(Socket* socket);
    void endGame();

    void nextCource(QString row, QString column, QString width, QString height);

public slots:
    void sendToAllClients(QString message);

private slots:
    void gameIsStarted();

private:
    QList<Socket*> clients;

    GameInfo* client1GameInfo;
    GameInfo* client2GameInfo;

    bool client1IsLoaded = false;
    bool client2IsLoaded = false;

    bool isStarted = false;

    int scoreFirstClient = 0;
    int scoreSecondClient = 0;

    QString colorFirst;
    QString colorSecond;

    int whoTurn;

    QMutex* roomMutex;
};

#endif // ROOM_H
