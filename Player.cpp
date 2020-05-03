#include "Player.h"

Player::Player(const string name, const string description, Room* room) :Thing(name, description) {
	Type = PLAYER;
	Location = room;
}

bool Player::PerformAction(vector<string>& action) {
	//Look at something
	if (action.at(0) == "look") {
		Look(action);
	}
	//Go in a specific direction
	else if (action.at(0) == "go" || action.at(0) == "north" || action.at(0) == "east" || action.at(0) == "west" || action.at(0) == "south") {
		system("CLS");
		Go(action);
	}
	//Get Item
	else if ((action.at(0) == "take" || action.at(0) == "get") && action.size() > 1) {
		Take(action);
	}
	//Drop Item
	else if ((action.at(0) == "drop" || action.at(0) == "release" || action.at(0) == "put") && action.size() > 1) {
		Drop(action);
	}
	//Check inventory
	else if (action.at(0) == "inventory") {
		Inventory();
	}
	//Open Things
	else if (action.at(0) == "open" && action.size() > 1) {
		Open(action);
	}
	//Close Things
	else if (action.at(0) == "close" && action.size() > 1) {
		Close(action);
	}
	//UnLook door with item
	else if (action.at(0) == "unlock" && action.size() > 3) {
		Unlock(action);
	}
	//Look door with item
	else if (action.at(0) == "lock" && action.size() > 3) {
		Lock(action);
	}
	else if (action.at(0) == "sit") {
		return Sit();
	}
	//Incorrect action
	else {
		cout << "I don't understand this action" << endl;
	}
	return false;
}

void Player::Look(const vector<string>& action) const {
	//Look around
	if (action.size() == 1) {
		Location->Look();
	}
	//Look specific object
	else {
		Thing* thing = HasItem(action.at(2));
		if (thing == NULL) {
			thing = Location->CheckItemExists(action.at(2));
		}
		if (thing != NULL) {
			Usable* item = (Usable*)thing;
			item->Look();
		}
		else {
			thing = Location->CheckExitExists(action.at(2));
			if (thing != NULL) {
				Exit* exit = (Exit*)thing;
				exit->Look();
			}
			else {
				cout << "There is no " << action.at(2) << " here." << endl;
			}
		}
	}

}

void Player::Go(vector<string>& action) {
	if (action.at(0) == "go" && action.size() > 1) {
		action.at(0) = action[1];
	}
	if (action.at(0) == "north" || action.at(0) == "east" || action.at(0) == "west" || action.at(0) == "south") {
		Exit* exit = Location->GetExit(action.at(0));
		if (exit == NULL) {
			cout << "There is no exit " << action.at(0);
		}
		else {
			if (exit->CheckOpen()) {
				Location = exit->ExitToRoom(Location);
				cout << "You take the exit and you get to the " << Location->GetName() << endl;
				Location->Look();
			}
			else {
				cout << "The door is closed";
			}
		}
	}
	else {
		cout << "This is not a valid direction." << endl;
	}
}

void Player::Take(const vector<string>& Item) {
	Thing* item = Location->GetItem(Item.at(1), true);
	if (item != NULL) {
		Container.push_back(item);
		cout << "Taken." << endl;
	}
}

void Player::Drop(const vector<string>& Things) {
	//Drop something into room
	if (Things.size() == 2) {
		Thing* item = GetItem(Things.at(1));
		if (item == NULL) {
			cout << "You don't have " << Things.at(1) << " in your inventory." << endl;
		}
		else {
			Location->InsertThing(item);
			cout << "Dropped." << endl;
		}
	}
	//Drop something into something
	else if (Things.size() == 4) {
		if (Things.at(1) != Things.at(3)) {
			Thing* playerItem = HasItem(Things.at(1));
			if (playerItem == NULL) {
				cout << "You don't have " << Things.at(1) << " in your inventory." << endl;
				return;
			}
			Thing* containerItem = NULL;
			containerItem = HasItem(Things.at(3));
			if (containerItem == NULL) {
				Thing* roomEntity = Location->CheckItemExists(Things.at(3));
				if (roomEntity == NULL) {
					cout << "There is no " << Things.at(3) << " in the room or in your inventory.";
					return;
				}
				containerItem = roomEntity;
			}
			Usable* item = (Usable*)containerItem;
			if (item->CheckOpenable()) {
				if (item->CheckOpen()) {
					containerItem->InsertThing(playerItem);
					Container.remove(playerItem);
					cout << "You put the " << Things.at(1) << " into the " << Things.at(3) << ".";
				}
				else {
					cout << "The " << Things.at(3) << " is closed. Open it first.";
				}
			}
			else {
				cout << "You can't put anything inside " << Things.at(3) << ".";
			}
		}
		else {
			cout << "You can't put an object inside itself!";
		}
	}
}

void Player::Inventory() const {
	if (Container.size() == 0) {
		cout << "Your inventory is empty";
	}
	else {
		cout << "You are carrying:";
		for (Thing* entity : Container) {
			if (entity->GetType() == ITEM) {
				cout << endl << entity->GetName() << ": " << entity->GetDescription();
			}
		}
	}
}

void Player::Open(const vector<string>& Things) const {
	if (Things.at(1) != "door") {
		Thing* entity = HasItem(Things.at(1));
		if (entity == NULL) {
			entity = Location->CheckItemExists(Things.at(1));
		}
		if (entity != NULL) {
			Usable* item = (Usable*)entity;
			item->Open();
		}
	}
	else {
		Location->OpenDoor();
	}
}

void Player::Close(const vector<string>& Things) const {
	if (Things.at(1) != "door") {
		Thing* entity = HasItem(Things.at(1));
		if (entity == NULL) {
			entity = Location->CheckItemExists(Things.at(1));
		}
		if (entity != NULL) {
			Usable* item = (Usable*)entity;
			item->Close();
		}
	}
	else {
		Location->CloseDoor();
	}
}

void Player::Unlock(const vector<string>& Things) const {
	Thing* playerItem = HasItem(Things.at(3));
	if (playerItem == NULL) {
		cout << "You don't have " << Things.at(3) << " in your inventory." << endl;
		return;
	}
	Location->UnlockDoor(playerItem);
}

void Player::Lock(const vector<string>& Things) const {
	Thing* playerItem = HasItem(Things.at(3));
	if (playerItem == NULL) {
		cout << "You don't have " << Things.at(3) << " in your inventory." << endl;
		return;
	}
	Location->LockDoor(playerItem);
}

bool Player::Sit() const {
	if (Location->GetName() == "Office") {
		Thing* Chair = Location->CheckItemExists("Chair");
		if (HasItem("usb") != NULL) {
			cout << "You finally sit on the chair and submit your project! Congratulations!";
			return true;
		}
		else {
			cout << "You have to find your USB first!";
		}
	}
	else {
		cout << "You are not in the work room.";
	}
	return false;
}

Thing* Player::GetItem(const string name) {
	for (Thing* entity : Container) {
		if (entity->GetType() == ITEM) {
			string itemName = entity->GetName();
			if (itemName == name) {
				Container.remove(entity);
				return entity;
			}
		}
	}
	return NULL;
}

Thing* Player::HasItem(const string name) const {
	for (Thing* entity : Container) {
		if (entity->GetType() == ITEM) {
			string itemName = entity->GetName();
			if (itemName == name) {
				return entity;
			}
		}
	}
	return NULL;
}

void Player::Look() const {
	cout << "My name is " << Name << " and " << Description << ".";
}