#include "CitiesModel.h"


class CitiesGame {
	CitiesModel game;
	string PlayerName;
	int cntPlayers=0;
public:
	CitiesGame(string dir);
	void mainMenu(int choice);
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
	void checkFiles(string &dir);
	void clearFiles();
};