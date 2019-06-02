#include "CitiesModel.h"
using namespace std;

CitiesModel::CitiesModel(string citiesDir) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	this->dir = citiesDir;
	loadCities();
}
string CitiesModel::getDir()const { return dir; }
int CitiesModel::checkCity(string answerCity) {
	if (cities.find(answerCity) == end(cities)) {
		if (oneOrMult == 1) {
			cout << "\n����� �� ������. � ��������� �� ���������.\n\n";
			return 1;
		}
		else
			cout << "\n����� �� ������. �� ��������� �� ����.\n\n";

	}
	//throw exception("����� �� ������!");
	vector<string> usedCities;
	fstream file(dir + "\\usedCities.csv", ios::in);
	try {
		if (!file)
			throw exception
			("\n\n (!) ������: ���� �� ������� ���������� ������� - usedCities.csv \n ��������� ��� �����������.\n �������������� ����.\n\n");
	}
	catch (exception&e) {
		cout << e.what();
		system("pause");
		exit(0);
	}
	while (!file.eof()) {
		string c;
		getline(file, c);
		if (c.size() > 0)
			usedCities.push_back(c);
	}
	file.close();
	if (usedCities.size() == 0) {
		file.open(dir + "\\usedCities.csv", ios::out);
		file << answerCity;
		file.close();
		return 4;
	}
	//answerCity;
	//usedCities;
	if (find(begin(usedCities), end(usedCities), answerCity)
		!= end(usedCities))
		throw exception("����� ��� �������������!");
	//������ ������
	char c = *((usedCities.end() - 1)->end() - 1);
	if (c == '�' || c == '�' || c == '�' ||
		c == '�')
		c = *((usedCities.end() - 1)->end() - 2);

	c -= 32;
	if (answerCity[0] != c) {
		string res = "����� �� ���������, ������ ���� ����� ";
		res.push_back(c);
		throw exception(res.c_str());
	}
	usedCities.push_back(answerCity);
	file.open(dir + "\\usedCities.csv", ios::out);
	for (auto&i : usedCities)
		file << i << endl;
	file.close();

}

void CitiesModel::loadCities() {
	ifstream file(dir + "\\city.csv");
	try {
		if (!file)
			throw exception
			("\n\n (!) ������: ���� �� ������� ������� - city.csv \n ��������� ��� �����������.\n �������������� ����.\n\n");
	}
	catch (exception&e) {
		cout << e.what();
		system("pause");
		exit(0);
	}
	string city;
	getline(file, city);

	while (!file.eof()) {
		getline(file, city);
		//4315;3159;4312;���������
		city = city.substr(city.rfind(';') + 1);
		cities.emplace(city, "");
	}
	file.close();
}
