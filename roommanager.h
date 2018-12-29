#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <QList>

class Room;
class Socket;
class QSqlDatabase;

class RoomManager
{
public:
    RoomManager();
    bool createRoom(Socket *socket1, Socket *socket2);
    static bool removeRoom_s(Room *room);
    bool removeRoom(Room *room);

private:
    QList<Room*> rooms;
};

#endif // ROOMMANAGER_H
