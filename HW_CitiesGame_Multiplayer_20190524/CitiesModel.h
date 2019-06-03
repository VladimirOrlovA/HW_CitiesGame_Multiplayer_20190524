#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <Windows.h>
using namespace std;

class CitiesModel {
	map<string, string> cities;
	string dir;
	int oneOrMult;
	int cntExceptions = 0;
public:
	void setOneOrMult(int oneOrMult) { this->oneOrMult = oneOrMult;};
	int getOneOrMult() const { return this->oneOrMult; };

	CitiesModel(string citiesDir);
	string getDir()const { return dir; };
	int checkCity(string answerCity);

private:
	void loadCities();
};