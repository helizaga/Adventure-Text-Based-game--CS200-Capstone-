#pragma once
#include "Thing.h"
#include "Room.h"

class Room;
enum Direction { 
	NORTH, WEST, EAST, SOUTH 
};

class Exit : public Thing {
private:
	Direction m_Direction;
	Room* Source;
	Room* Destination;
	bool IsOpen;
	bool IsLocked;
	bool IsLockable;

public:
	Exit(const string name, const string description, Direction direction, Room* source, Room* destination, bool open, bool locked, bool lockable);
	void Look(const Room* room) const;
	void Look() const;
	string GetExitDirection(const Room* room) const;
	Room* ExitToRoom(const Room* room) const;
	bool CheckOpen();
	bool Open();
	bool Close();
	bool Unlock(Thing* key);
	bool Lock(Thing* key);
};

