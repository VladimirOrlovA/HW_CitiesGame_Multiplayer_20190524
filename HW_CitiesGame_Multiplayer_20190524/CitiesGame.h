#include "CitiesModel.h"


class CitiesGame {
	CitiesModel game;
	string userName;
	int cntPlayers=0;
public:
	CitiesGame(string dir);
	void menu(int choice);
	void menuAfterPlay();
	void multiPlayer();
	void singlePlayer();
	void players();
	void nowPlay();
	void start();
	void info();
private:
	char getLastLetter();
	string getLastCity();
};