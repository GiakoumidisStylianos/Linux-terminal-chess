#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

int main() {

	char ans;
	string filePath = "";
	while(1) {
		cout << "Do you wish to load a previous game? (y/n): ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			cout << "Enter file path: ";
			filePath;
			cin >> filePath;
			break;
		}
		else if (ans == 'n' || ans == 'N') {
			break;
		}
	}
	
	Game game(filePath);
    game.startGame();
    return 0;
}