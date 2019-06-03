#pragma once
#include"CitiesGame.h"


CitiesGame::CitiesGame(string dir)
	:game(dir) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int r = 10 + rand() % 6;
	int x = 0;
	for (size_t i = 0; i < r; i++)
	{
		cout << "\n\n -= Добро пожаловать в игру ГОРОДА! =- \n\n";
		cout << "Загрузка ";
		for (size_t i = 0; i < x; i++)
		{
			cout << ">";
		}
		Sleep(0);
		x++;
		if (x == 4) x = 0;
		system("cls");
	}
	checkFiles(dir);
}
void CitiesGame::mainMenu(int choice)
{
	Sleep(2000);
	system("cls");
	while (choice)
	{
		if (choice != 4) {
			cout << "\n\n -= Главное меню =- \n\n"
				<< "1. Игра по сети\n"
				<< "2. Игра одиночная - тренировка\n"
				<< "3. Информация об игре\n"
				<< "4. Выход\n"
				<< "\n-> ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			system("cls");
			cin.get();
			multiPlayer();
			break;
		case 2:
			system("cls");
			singlePlayer();
			break;
		case 3:
			system("cls");
			info();
			break;
		case 4:
			system("cls");
			choice = 0;
			clearFiles();
			cout << "\n\nСпасибо! До_свидания :) \n\n";
			exit(0);
		default:
			cout << "\nОшибочный ввод номера меню. Попробуйте еще раз...\n";
			Sleep(2000);
			system("cls");
		}
	}
}
void CitiesGame::menuAfterPlay()
{
	Sleep(2000);
	system("cls");
	cout << "\nЧто будем делать дальше: \n\n";
	int choice = 1;
	while (choice) {
		cout << "1. - продолжить играть \n"
			<< "2. - пройти в главное меню \n"
			<< "3. - выход из игры \n"
			<< "\n-> ";

		cin >> choice;
		switch (choice)
		{
		case 1:
			start();
			//return;
			break;
		case 2:
			system("cls");
			mainMenu(1);
			break;
		case 3:
			system("cls");
			mainMenu(4);
			break;
		default:
			cout << "\nОшибочный ввод номера меню. Попробуйте еще раз...\n";
			Sleep(2000);
			system("cls");
		}
	}
}
void CitiesGame::multiPlayer()
{
	players();
}
void CitiesGame::singlePlayer()
{
	game.setOneOrMult(1);
	cntPlayers = 1;
	players();
}
void CitiesGame::players()
{
	fstream listOfPlayers(game.getDir() + "\\listOfPlayers.csv", ios::in); ///////???????????????
	string name;
	if (game.getOneOrMult() != 1) {
		getline(listOfPlayers, name);
		while (!listOfPlayers.eof()) {
			getline(listOfPlayers, name);
			cntPlayers++;
		}
		cout << "\nВ игре участвует " << cntPlayers << " игроков!";
	}
	else {
		listOfPlayers.close();
		listOfPlayers.open(game.getDir() + "\\listOfPlayers.csv", ios::out | ios::trunc);
	}

	cout << "\n\nВведите свое имя для начала игры! \n\n-> ";
	cin.get();
	getline(cin, name);
	listOfPlayers.close();
	listOfPlayers.open(game.getDir() + "\\listOfPlayers.csv", ios::out | ios::app);
	if (game.getOneOrMult() == 1)
		listOfPlayers << name << ";1\n";
	else
		listOfPlayers << name << ";0\n";
	PlayerName = name;
	listOfPlayers.close();
	start();
}
void CitiesGame::start() {

	while (1) {
		vector<pair<string, char>> players;
		int flag = 0;
		while (flag != 1) {
			fstream users(game.getDir() + "\\listOfPlayers.csv");
			players.clear();
			while (!users.eof()) {
				string tmp;
				getline(users, tmp);
				if (tmp.size() > 0) {
					//петя;0
					string name = tmp.substr(0, tmp.size() - 2);
					char c = tmp[tmp.size() - 1];
					if (c == '1')//&&userName == name)
						flag = 1;
					if (c == '1') {
						system("cls");
						cout << "Ходит " << name << endl;
					}
					players.push_back(make_pair(name, c));
				}
			}
			users.close();
			Sleep(1000);
			system("cls");
		}
		//Значит мы ходим
		int choice = 0;
		while (choice != 1) {
			if (!empty(getLastCity())) {
				cout << "Последний город " << getLastCity() << endl;
				cout << "Введите город на букву " << getLastLetter() << "\n-> ";
			}
			else cout << "Введите первый город \n-> ";
			string answer;
			getline(cin, answer);
			system("cls");
			//try {
			//	game.checkCity(answer);
			//	//choice = 1;
			//	if (game.checkCity(answer) == 1)
			//		menuAfterPlay();
			//}
			//catch (exception&e) {
			//	//cout << e.what();
			//	system("pause");
			//	system("cls");
			//}
			//game.checkCity(answer);
			if (game.checkCity(answer) == 1)
				mainMenu(1); //menuAfterPlay();
		}
		//считываем текущих игроков
		fstream listOfPlayers(game.getDir() + "\\listOfPlayers.csv");
		players.clear();
		int pos;
		while (!listOfPlayers.eof()) {
			string tmp;
			getline(listOfPlayers, tmp);
			if (tmp.size() > 0) {
				//петя;0
				string name = tmp.substr(0, tmp.size() - 2);
				char c = tmp[tmp.size() - 1];

				if (c == '1')
					pos = players.size();
				players.push_back(make_pair(name, c));
			}
		}
		listOfPlayers.close();
		players[pos].second = '0';
		pos++;
		if (pos == players.size())
			pos = 0;
		players[pos].second = '1';
		listOfPlayers.open(game.getDir() + "\\listOfPlayers.csv");
		for (auto&i : players) {
			listOfPlayers << i.first << ";" << i.second << endl;
		}
		listOfPlayers.close();
		system("cls");
	}
}
void CitiesGame::info()
{
	int anyKey = 1;
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "Города́ — игра для нескольких(двух или более) человек, в которой каждый " <<
		"участник в свою очередь называет реально существующий город любой страны, " <<
		"название которого начинается на ту букву, которой оканчивается название " <<
		"предыдущего участника\n\n";
	cout << "\n\n\n\n\n\n\n";
	system("pause");
	system("cls");
}
char CitiesGame::getLastLetter() {
	fstream file(game.getDir() + "\\usedCities.csv");
	string str;
	while (!file.eof()) {
		string s;
		getline(file, s);
		//cout << s;
		if (s.size() > 0)
			str += s;
	}
	file.close();
	if (str.size() == 0) return '0';
	if (str[str.size() - 1] == 'ь'
		|| str[str.size() - 1] == 'ы'
		|| str[str.size() - 1] == 'й' ||
		str[str.size() - 1] == 'ц')
		return str[str.size() - 2] - 32;

	return str[str.size() - 1] - 32;
}
string CitiesGame::getLastCity() {
	fstream usedCities(game.getDir() + "\\usedCities.csv");

	string str;
	/*if (usedCities.eof())
		cout << " - еще нет \n";*/
	while (!usedCities.eof()) {
		string s;
		getline(usedCities, s);
		//cout << s;
		if (s.size() > 0)
			str = s;
	}
	usedCities.close();

	return str;
}
void CitiesGame::checkFiles(string &dir)
{
	fstream listOfCities(dir + "\\listOfCities.csv");
	fstream listOfPlayers(dir + "\\listOfPlayers.csv");
	fstream usedCities(dir + "\\usedCities.csv");
	try {
		if (!listOfCities)
			throw exception
			("\n\n (!) Ошибка: Файл со списком городов - listOfCities.csv \n поврежден или отсутствует.\n Переустановите игру.\n\n");
		if (!listOfPlayers)
			throw exception
			("\n\n (!) Ошибка: Файл со списком игроков - users.csv поврежден или отсутствует.\nПереустановите игру.\n\n");
		if (!usedCities)
			throw exception
			("\n\n (!) Ошибка: Файл со списком отыгравших городов - usedCities.csv \n поврежден или отсутствует.\n Переустановите игру.\n\n");
	}
	catch (exception&e) {
		cout << e.what();
		system("pause");
		exit(0);
	}
	/*listOfCities.close();
	listOfPlayers.close();
	usedCities.close();*/
	mainMenu(1);
}
void CitiesGame::clearFiles()
{
	fstream listOfPlayers(game.getDir() + "\\listOfPlayers.csv", ios::out);
	listOfPlayers.open(game.getDir() + "\\listOfPlayers.csv", ios::out | ios::trunc);
	listOfPlayers.close();

	fstream usedCities(game.getDir() + "\\usedCities.csv", ios::out);
	usedCities.open(game.getDir() + "\\usedCities.csv", ios::out | ios::trunc);
	usedCities.close();
}
