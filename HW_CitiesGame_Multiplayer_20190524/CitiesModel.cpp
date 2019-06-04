#include "CitiesModel.h"
using namespace std;

CitiesModel::CitiesModel(string citiesDir) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	this->dir = citiesDir;
	loadCities();
}
int CitiesModel::checkCity(string answerCity) {
	try {
		if (cities.find(answerCity) == end(cities))
			throw exception("\n\n  Город не найден. ");

		vector<string> usedCities;
		fstream file(dir + "\\usedCities.csv", ios::in); // открываем на чтение

		while (!file.eof()) {
			string c;
			getline(file, c);
			if (c.size() > 0)
				usedCities.push_back(c);
		}
		file.close();
		
		//answerCity;
		//usedCities;
		if (find(begin(usedCities), end(usedCities), answerCity)
			!= end(usedCities))
			throw exception("\n\nГород уже использовался! ");
		
		if (usedCities.size() == 0) {
			file.open(dir + "\\usedCities.csv", ios::out);
			file << answerCity;
			file.close();
			return 10;
		}
		
		
		
		//Алматы Тамбов
		char c = *((usedCities.end() - 1)->end() - 1);
		if (c == 'ь' || c == 'ы' || c == 'й' ||
			c == 'ц')
			c = *((usedCities.end() - 1)->end() - 2);

		c -= 32;
		if (answerCity[0] != c) {
			string res = "\n\nБуквы не совпадают, должна быть буква - ";
			res.push_back(c);
			throw exception(res.c_str());
		}

		usedCities.push_back(answerCity);
		file.open(dir + "\\usedCities.csv", ios::out);
		for (auto&i : usedCities)
			file << i << endl;
		file.close();
	}
	catch (exception &e) {
		
		if (oneOrMult == 1) {
			cout << e.what() << "\n\n !!! К сожалению Вы проиграли !!! \n\n";
			Sleep(2000);
			system("cls");
			answerCity.clear();
			return 1;
		}
		else {
			cout << e.what() << "\n\n!!! Вы выбываете из игры. !!! \n\n";
			Sleep(2000);
			system("cls");
			return 2;
		}
	}
}

void CitiesModel::loadCities() {
	ifstream listOfCities(dir + "\\listOfCities.csv");
	string city;
	getline(listOfCities, city);

	while (!listOfCities.eof()) {
		getline(listOfCities, city);
		//4315;3159;4312;Апрелевка
		city = city.substr(city.rfind(';') + 1);
		cities.emplace(city, "");
	}
	listOfCities.close();
}
