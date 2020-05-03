#include "Room.h"

Room::Room(const string name, const string description) : Thing(name, description) {
	Type = ROOM;
}

void Room::Look() const {
	cout << endl << Name << endl << Description << ".";
	for (Thing* Obj : Container) {
		if (Obj->GetType() == EXIT)	{
			Exit* pExit = (Exit*)Obj;
			pExit->Look(this);
		}
	}
	for (Thing* Obj : Container) {
		if (Obj->GetType() == ITEM) {
			Usable* Item = (Usable*)Obj;
			Item->Look();
		}
	}
}

Exit* Room::GetExit(const string direction) const {
	for (Thing* Obj : Container) {
		if (Obj->GetType() == EXIT) {
			Exit* pExit = (Exit*)Obj;
			string exitDirection = pExit->GetExitDirection(this);
			if (exitDirection == direction) {
				return pExit;
			}
		}
	}
	return NULL;
}

Thing* Room::GetItem(const string name, const bool remove) {
	for (Thing* entity : Container) {
		if (entity->GetType() == ITEM) {
			string itemName = entity->GetName();
			if (itemName == name) {
				if (((Usable*)entity)->CheckMovable()) {
					if (remove) {
						Container.remove(entity);
					}
					return entity;
				}
				else {
					cout << "You can't carry this.";
					return NULL;
				}
			}
			else {
				Usable* item = (Usable*)entity;
				Thing* insideItem = item->GetInsideItem(name);
				if (insideItem != NULL) {
					return insideItem;
				}
			}
		}
	}
	cout << "There is not " << name << "." << endl;
	return NULL;
}

Thing* Room::CheckItemExists(const string name) const {
	for (Thing* entity : Container) {
		if (entity->GetType() == ITEM) {
			string itemName = entity->GetName();
			if (itemName == name){
				return entity;
			}
		}
	}
	return NULL;
}

Thing* Room::CheckExitExists(const string name) const {
	for (Thing* entity : Container) {
		if (entity->GetType() == EXIT) {
			string itemName = entity->GetName();
			if (itemName == name) {
				return entity;
			}
		}
	}

	return NULL;
}

void Room::OpenDoor() const {
	for (Thing* entity : Container) {
		if (entity->GetType() == EXIT) {
			Exit* pExit = (Exit*)entity;
			if (pExit->Open()) {
				return;
			}
		}
	}
	cout << "There is no door in the room that can be opened.";
}

void Room::CloseDoor() const {
	for (Thing* entity : Container) {
		if (entity->GetType() == EXIT) {
			Exit* pExit = (Exit*)entity;
			if (pExit->Close()) {
				return;
			}
		}
	}
	cout << "There is no door in the room that can be closed.";
}

void Room::UnlockDoor(Thing* key) const {
	for (Thing* entity : Container) {
		if (entity->GetType() == EXIT) {
			Exit* pExit = (Exit*)entity;
			if (pExit->Unlock(key)) {
				return;
			}
		}
	}
	cout << "There is no door in the room that can be unlocked with the " << key->GetName() << ".";
}

void Room::LockDoor(Thing* key) const {
	for (Thing* entity : Container) {
		if (entity->GetType() == EXIT) {
			Exit* pExit = (Exit*)entity;
			if (pExit->Lock(key)) {
				return;
			}
		}
	}
	cout << "There is no door in the room that can be locked by the " << key->GetName() << ".";
}