#ifndef SEARCHGAME_H
#define SEARCHGAME_H

#include <QThread>

class Socket;
class QMutex;
class QTimer;
class RoomManager;

class SearchGame : public QThread
{
    Q_OBJECT
public:
    SearchGame(RoomManager* rm);
    void run();
    static bool addNewClientInSearch_s(Socket* client);
    void addNewClientInSearch(Socket* client);

private slots:
    void searchGame();

private:
    QList<Socket*> clients;
    QMutex* mutexClients;
    QTimer* searchGameTimer;
    RoomManager* roomManager;
    QString typeGame;
};

#endif // SEARCHGAME_H
