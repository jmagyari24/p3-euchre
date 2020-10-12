#include "Pack.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Game {
public:
	Game(ifstream& pack_in, string points_to_win, vector <Player*>& players) {
		pack = Pack(pack_in);
		points_to_win = points_to_win;
		players_game = players;
	}

	void shuffle(const string shuffleMode) {
		if (shuffleMode == "noshuffle") {
			//pack.reset();
		}
		if (shuffleMode == "shuffle") {
			//pack.shuffle();
		}
	}



private:
	Pack pack;
	int points_to_win;
	vector <Player*> players_game;
	
};


int main(int argc, char **argv) {
	//Make sure parameters are valid
	try {
		if (argc != 12) {
			throw;
		}
		if (stoi(argv[3]) < 1 || stoi(argv[3]) > 100) {
			throw argv[3];
		}
		if (!(argv[2] == "shuffle" || argv[2] == "noshuffle")) {
			throw;
		}
		for (int i = 5; i < 12; i = i + 2) {
			if (!(argv[i] == "Simple" || argv[i] == "Human")) {
				throw;
			}
		}
	}
	catch(...) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return -1;
	}
	//Open pack
	ifstream pack_filename;
	pack_filename.open(argv[1]);
	if (!pack_filename.is_open()) {
		cout << "Error opening " << argv[1] << endl;
		return -1;
	}
	vector <Player*> players;
	for (int i = 4; i < 8; i++) {
		players[i] = Player_factory(argv[i], argv[i + 1]);
	}
	Game game(pack_filename, argv[3], players);
	pack_filename.close();
	//Create players (remember to delete them at the end)


	




	for (int i = 4; i < 8; i++) {
		delete argv[i+2];
	}
	return 0;
}