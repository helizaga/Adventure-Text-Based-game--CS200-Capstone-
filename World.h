#pragma once
#include <string>
#include <time.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Thing.h"
#include "Player.h"

using namespace std;

class World {
private:
	vector<Thing*> Things;
	Player* User;
	const int MAX_NUMBER_OF_TURNS = 35;
	int NumberOfTurnsPlayed = 0;
	bool RUNNING = true;
	void RestartGame();
	vector<string> SimplifyInput(string action);
	void CreateThings();
	void AddIntroduction();
public:
	World();
	void StartGame();
};