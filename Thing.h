#pragma once
#include <string>
#include <list>
#include <iostream>
#include <vector>

using namespace std;

enum ThingType {
	ROOM, EXIT, PLAYER, ITEM
};

class Thing {
protected:
	ThingType Type;
	string Name;
	string Description;
	list<Thing*> Container;
public:
	Thing(const string name, const string description);
	virtual void Look() const = 0;
	ThingType GetType() const;
	string GetName() const;
	string GetDescription() const;
	void InsertThing(Thing* entity);
};