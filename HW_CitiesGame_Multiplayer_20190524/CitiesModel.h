#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <Windows.h>
using namespace std;

class CitiesModel {
	map<string,string> cities;
	string dir;
	int oneOrMult;
	/*int endGame=0;
	int cntPlayers = 0;*/
public:
	void setOneOrMult(int oneOrMult) { this->oneOrMult = oneOrMult;};
	int getOneOrMult() const { return this->oneOrMult; };

	//void setEndGame(int endGame) { this->endGame = endGame; };
	//int getEndGame() const { return this->endGame; };

	//void setCntPlayers(int endGame) { this->cntPlayers = cntPlayers; };
	//int getCntPlayers() const { return this->cntPlayers; };

	CitiesModel(string citiesDir);
	string getDir()const;
	int checkCity(string answerCity);

private:
	void loadCities();
};