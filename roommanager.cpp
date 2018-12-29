#include "roommanager.h"
#include "room.h"
#include "socket.h"

static RoomManager* manager;

RoomManager::RoomManager()
{
    manager = this;
}

bool RoomManager::createRoom(Socket *socket1, Socket *socket2)
{
    Room* room = new Room(socket1, socket2);
    if(room == nullptr)
    {
        return false;
    }
    rooms.append(room);
    return true;
}

bool RoomManager::removeRoom_s(Room *room)
{
    return manager->removeRoom(room);
}

bool RoomManager::removeRoom(Room* room)
{
    if(!rooms.removeOne(room))
    {
        return false;
    }

    return true;
}
