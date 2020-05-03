#include "World.h"
#include "Exit.h"
#include "Usable.h"

World::World() {
	CreateThings();
}

void World::StartGame() {
	AddIntroduction();
	string input;
	vector<string>startAction{ "look" };
	User->PerformAction(startAction);
	cout << endl << endl;
	while (true) {
		//Check if playing or player has lost/won
		if (!RUNNING) {
			cout << "Do you want to play again? Yes or no?" << endl; 
			while (true) {
				cout << "=> ";
				getline(cin, input);
				vector<string> Inputs = SimplifyInput(input);
				if (Inputs.at(0) == "yes" || Inputs.at(0) == "y") {
					cout << endl << endl;
					RestartGame();
					AddIntroduction();
					break;
				}
				else if (Inputs.at(0) == "no" || Inputs.at(0) == "n") {
					cout << "Game Exiting....";
					return;
				}
			}
		}
		//Getting user input
		cout << endl << endl << "-- " << NumberOfTurnsPlayed << "/" << MAX_NUMBER_OF_TURNS <<" actions --" << endl;
		cout << "=> ";
		getline(cin, input);
		if (!input.empty()) {
			vector<string> tokens = SimplifyInput(input);
			//Stop playing
			if (tokens.at(0) == "quit" || tokens.at(0) == "leave" || tokens.at(0) == "exit") {
				cout << "Game Exiting....";
				break;
			}
			if (tokens.size() > 0) {
				bool finish = User->PerformAction(tokens);
				if (finish) {
					cout << endl << "             CONGRATULATIONS" << endl;
					cout << "You submitted your project and are awaiting your grade!!" << endl << endl;
					RUNNING = false;
				}
			}
		}
		else {
			cout << "Write something" << endl;
		}
		NumberOfTurnsPlayed++;
		if (NumberOfTurnsPlayed >= MAX_NUMBER_OF_TURNS && RUNNING) {
			RUNNING = false;
			cout << "You have run out of turns!!" << endl << endl << "YOU LOSE" << endl << endl;
		}
	}
}

//Private methods

void World::RestartGame() {
	NumberOfTurnsPlayed = 0;
	RUNNING = true;
	CreateThings();
}

vector<string> World::SimplifyInput(string input) {
	//Lowercasing input to improve the comparison
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	//Removing empty spaces and separate words
	istringstream buffer(input);
	vector<string> inputs { 
		istream_iterator<string>{buffer}, istream_iterator<string>{} 
	};
	return inputs;
}

void World::CreateThings() {
	Things.clear();

	//Rooms
	Room* Entrance = new Room("Entrance", "A relatively empty room");
	Room* LivingRoom = new Room("Living Room", "Big living room with a couch, a TV, and a coffee table");
	Room* Bedroom = new Room("Bedroom", "Small bedroom with a bed and a chair");
	Room* Office = new Room("Office", "A small room with a desk, computer and a chair");
	Room* Kitchen = new Room("Kitchen", "There is a fridge in here and a backpack leaning against the wall");
	Room* Upstairs = new Room("Upstairs", "A small storage room; it could converted to a small bedroom");
	Things.push_back(Entrance);
	Things.push_back(LivingRoom);
	Things.push_back(Bedroom);
	Things.push_back(Office);
	Things.push_back(Kitchen);
	Things.push_back(Upstairs);
	//Exits
	Exit* Exit1 = new Exit("open doorway", "", NORTH, Entrance, LivingRoom, true, false, false);
	Exit* Exit2 = new Exit("passage", "", WEST, LivingRoom, Bedroom, true, false, false);
	Exit* Exit3 = new Exit("door", "made of wood", NORTH, Bedroom, Office, false, true, true);
	Exit* Exit4 = new Exit("corridor", "", EAST, LivingRoom, Kitchen, true, false, false);
	Exit* Exit5 = new Exit("stairs", "", NORTH, LivingRoom, Upstairs, true, false, false);
	Things.push_back(Exit1);
	Things.push_back(Exit2);
	Things.push_back(Exit3);
	Things.push_back(Exit4);
	Things.push_back(Exit5);
	//Items
	Usable* Chest = new Usable("chest", "(there might be something inside).", Entrance, NULL, true, false, NULL, false);
	Usable* Coffee = new Usable("coffee on table", "half-full from this morning's brew.", LivingRoom, NULL, true, false, NULL, true);
	Usable* Paper = new Usable("paper", "which reads: 'Please give me an A on this project!'", NULL, Chest, false, false, NULL, true);
	Usable* Backpack = new Usable("backpack", "that you use for school.", Kitchen, NULL, true, false, NULL, true);
	Usable* Oven = new Usable("oven", ", it has something that smells good.", Kitchen, NULL, true, false, NULL, false);
	Usable* Pizza = new Usable("pizza", ", extremely cheesy.", NULL, Oven, false, false, NULL, true);
	Usable* USB = new Usable("usb", "that contains your semester's project.", NULL, Backpack, false, false, NULL, true);
	Usable* Key = new Usable("key", "that unlocks a room.", Upstairs, NULL, false, false, Exit3, true);
	Usable* Closet = new Usable("closet", "full of clothes.", Bedroom, NULL, true, true, NULL, false);
	Usable* Chair = new Usable("chair", "in front of your desktop computer.", Office, NULL, true, false, NULL, false);

	Things.push_back(Chest);
	Things.push_back(Coffee);
	Things.push_back(Paper);
	Things.push_back(Backpack);
	Things.push_back(Oven);
	Things.push_back(Pizza);
	Things.push_back(USB);
	Things.push_back(Key);
	Things.push_back(Closet);
	Things.push_back(Chair);
	//Player
	User = new Player("Hans", "I have to turn in my assignment", Entrance);
	Things.push_back(User);
}

void World::AddIntroduction() {
	cout << "Welcome to 'Operation: Submit Project' text adventure!" << endl << endl;
	cout << "Procrastinating to submit your project to CANVAS, you realized you have 10 minutes before the submission deadline." << endl;
	cout << "Find your USB and get to your computer and submit it before it's too late!" << endl;
}