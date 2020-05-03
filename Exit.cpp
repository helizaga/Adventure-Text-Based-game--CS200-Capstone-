#include "Exit.h"

Exit::Exit(const string name, const string description, Direction direction, Room* source , Room* destination, bool open, bool locked, bool lockable) :Thing(name, description)
{
	Type = EXIT;
	m_Direction = direction;
	Source = source;
	Destination = destination;
	IsOpen = open;
	IsLocked = locked;
	IsLockable = lockable;
	Source->InsertThing(this);
	Destination->InsertThing(this);
}

void Exit::Look(const Room* room) const {
	cout << endl << "There is a " << Name << " " << Description << " in the " << GetExitDirection(room) << " part of the room.";
}

void Exit::Look() const {
	cout << endl << "There is a " << Name << " " << Description << " in the room.";
}

string Exit::GetExitDirection(const Room* room) const {
	bool fromSource = (room == Source);
	switch (m_Direction) {
	case NORTH:
		return fromSource ? "north" : "south";
	case SOUTH:
		return fromSource ? "south" : "north";
	case EAST:
		return fromSource ? "east" : "west";
	case WEST:
		return fromSource ? "west" : "east";
	}
	return "";
}

Room* Exit::ExitToRoom(const Room* room) const {
	if (room == Source) {
		return Destination;
	}
	else {
		return Source;
	}
}

bool Exit::CheckOpen() {
	return IsOpen;
}

bool Exit::Open() {
	if (Name == "door") {
		if (IsOpen) {
			cout << "The door is already open";
			return true;
		}
		else if (IsLocked) {
			cout << "The door is locked. It seems that you need a " << Container.front()->GetName() << ".";
			return true;
		}
		else {
			IsOpen = true;
			cout << "You open the door.";
			return true;
		}
	}
	else {
		return false;
	}
}

bool Exit::Close() {
	if (Name == "door") {
		if (IsOpen) {
			IsOpen = false;
			cout << "You close the door";
			return true;
		}
		else {
			cout << "The door is already closed.";
			return true;
		}
	}
	else {
		return false;
	}
}

bool Exit::Unlock(Thing* key) {
	if (IsLockable && (find(Container.begin(), Container.end(), key) != Container.end())) {
		if (IsLocked) {
			IsLocked = false;
			cout << "You unlock the door";
			return true;
		}
		else {
			cout << "The door is already unlocked.";
			return true;
		}
	}
	return false;
}

bool Exit::Lock(Thing* key) {
	if (IsLockable && (find(Container.begin(), Container.end(), key) != Container.end())) {
		if (IsLocked) {
			cout << "The door is already locked.";
			return true;
		}
		else {
			IsLocked = true;
			IsOpen = false;
			cout << "You lock the door";
			return true;
		}
	}
	return false;
}