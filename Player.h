#pragma once
#include "Thing.h"
#include "Room.h"

class Player : public Thing {
private:
	Room* Location;
	Thing* GetItem(const string name);
	Thing* HasItem(const string name) const;
	void Look(const vector<string>& action) const;
	void Go(vector<string>& action);
	void Take(const vector<string>& action);
	void Drop(const vector<string>& action);
	void Inventory() const;
	void Open(const vector<string>& action) const;
	void Close(const vector<string>& action) const;
	void Unlock(const vector<string>& action) const;
	void Lock(const vector<string>& action) const;
	bool Sit() const;
	void Look() const;
public:
	Player(const string name, const string description, Room* room);
	bool PerformAction(vector<string>& action);
};
