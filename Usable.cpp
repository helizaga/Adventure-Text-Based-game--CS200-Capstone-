#include "Usable.h"

Usable::Usable(const string name, const string description, Room* room, Usable* container, bool openable, bool open, Exit* exit, bool movable) :Thing(name, description) {
	Type = ITEM;
	IsOpen = open;
	IsOpenable = openable;
	IsMovable = movable;
	if (room != NULL) {
		room->InsertThing(this);
	}
	if (container != NULL) {
		container->InsertThing(this);
	}
	if (exit != NULL) {
		exit->InsertThing(this);
	}
}

void Usable::Look() const {
	cout << endl << "There is a " << Name << " " << Description;
	if (Container.size() > 0 && IsOpen) {
		cout << endl << "The " << Name << " is open:";
		for (Thing* entity : Container) {
			Usable* item = (Usable*)entity;
			item->Look();
		}
	}
}

void Usable::Open() {
	if (IsOpenable) {
		if (IsOpen) {
			cout << "It's already open.";
		}
		else {
			IsOpen = true;
			cout << "You open the " << Name;
			for (Thing* entity : Container) {
				Usable* item = (Usable*)entity;
				item->Look();
			}
		}
	}
	else {
		cout << "You can't open this";
	}
}

void Usable::Close() {
	if (IsOpenable) {
		if (IsOpen) {
			IsOpen = false;
			cout << "You close the " << Name;
		}
		else {
			cout << "It's already close.";
		}
	}
	else {
		cout << "You can't close this";
	}
}

bool Usable::CheckOpen() const {
	return IsOpen;
}

bool Usable::CheckOpenable() const {
	return IsOpenable;
}

bool Usable::CheckMovable() const {
	return IsMovable;
}

Thing* Usable::GetInsideItem(string name) {
	if (IsOpenable && IsOpen) {
		for (Thing* entity : Container) {
			if (entity->GetType() == ITEM && entity->GetName() == name) {
				Container.remove(entity);
				return entity;
			}
		}
	}
	return NULL;
}
