#include "Thing.h"

Thing::Thing(const string name, const string description) {
	Name = name;
	Description = description;
}

ThingType Thing::GetType() const {
	return Type;
}

string Thing::GetName() const {
	return Name;
}

string Thing::GetDescription() const {
	return Description;
}

void Thing::InsertThing(Thing* thing) {
	Container.push_back(thing);
} 