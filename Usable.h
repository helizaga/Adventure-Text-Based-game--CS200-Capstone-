#pragma once
#include "Thing.h"
#include "Room.h"

class Room;
class Exit;

class Usable : public Thing {
private:
	bool IsOpen;
	bool IsOpenable;
	bool IsMovable;

public:
	Usable(const string name, const string description, Room* room, Usable* container, bool openable, bool isOpen, Exit* exit, bool movable);
	void Look() const;
	void Open();
	void Close();
	bool CheckOpen() const;
	bool CheckOpenable() const;
	bool CheckMovable() const;
	Thing* GetInsideItem(string name);
};
