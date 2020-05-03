#pragma once
#include "Thing.h"
#include "Exit.h"
#include "Usable.h"

class Exit;
class Usable;

class Room : public Thing {
public:
	Room(const string name, const string description);
	void Look() const;
	Exit* GetExit(const string direction) const;
	Thing* GetItem(const string itemName, const bool remove);
	Thing* CheckItemExists(const string itemName) const;
	Thing* CheckExitExists(const string exitName) const;
	void OpenDoor() const;
	void CloseDoor() const;
	void UnlockDoor(Thing* key) const;
	void LockDoor(Thing* key) const;
};
