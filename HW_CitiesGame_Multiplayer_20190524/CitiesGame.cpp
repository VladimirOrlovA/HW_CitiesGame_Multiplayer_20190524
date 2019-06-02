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
		cout << "Добро пожаловать в игру ГОРОДА!\n\n";
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
	menu(1);
}
void CitiesGame::menu(int choice)
{
	while (choice)
	{
		if (choice != 4) {
			cout << "\n\nГлавное меню:\n\n" 
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
			cin.get();
			multiPlayer();
			break;
		case 2:
			singlePlayer();
			break;
		case 3:
			info();
			break;
		case 4:
			choice = 0;
			system("cls");
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
			return;
			break;
		case 2:
			system("cls");
			menu(1);
			break;
		case 3:
			system("cls");
			menu(4);
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
	players();
}
void CitiesGame::players()
{
	fstream users(game.getDir() + "\\users.csv", ios::in);
	try {
		if (!users)
			throw exception
			("\n\n (!) Ошибка: Файл со списком игроков - ""users.csv"" поврежден или отсутствует.\nПереустановите игру.\n\n");
	}
	catch (exception&e) {
		cout << e.what();
		system("pause");
		exit(0);
	}
	string name;
	if (game.getOneOrMult() != 1) {
		getline(users, name);
		while (!users.eof()) {
			getline(users, name);
			cntPlayers++;
		}
		cout << "\nВ игре участвует " << cntPlayers << " игроков!";
	}
	else {
		users.close();
		users.open(game.getDir() + "\\users.csv", ios::out | ios::trunc);
		cin.get();
	}
	cout << "\n\nВведите свое имя для начала игры!\n";

	getline(cin, name);
	users.close();
	users.open(game.getDir() + "\\users.csv", ios::out | ios::app);
	if (cntPlayers == 0)
		users << name << ";1\n";
	else
		users << name << ";0\n";
	userName = name;
	users.close();
	start();
}

void CitiesGame::start() {

	while (1) {
		vector<pair<string, char>> players;
		int flag = 0;
		while (flag != 1) {
			fstream users(game.getDir() + "\\users.csv");
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
					if (c == '1')
						cout << "Ходит " << name << endl;
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
			cout << "Последний город " << getLastCity() << endl;
			cout << "Введите город на букву " << getLastLetter() << endl;
			string answer;
			getline(cin, answer);
			try {
				game.checkCity(answer);
				choice = 1;
				//if (game.checkCity(answer) == 1 &&  menuChoice==2) //game.getOneOrMult() == 1)
				if (game.getOneOrMult() == 1)
					menuAfterPlay();
			}
			catch (exception&e) {
				cout << e.what();
				system("pause");
				system("cls");
			}
		}
		//считываем текущих игроков
		fstream users(game.getDir() + "\\users.csv");
		players.clear();
		int pos;
		while (!users.eof()) {
			string tmp;
			getline(users, tmp);
			if (tmp.size() > 0) {
				//петя;0
				string name = tmp.substr(0, tmp.size() - 2);
				char c = tmp[tmp.size() - 1];

				if (c == '1')
					pos = players.size();
				players.push_back(make_pair(name, c));
			}
		}
		users.close();
		players[pos].second = '0';
		pos++;
		if (pos == players.size())
			pos = 0;
		players[pos].second = '1';
		users.open(game.getDir() + "\\users.csv");
		for (auto&i : players) {
			users << i.first << ";" << i.second << endl;
		}
		users.close();
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
	fstream file(game.getDir() + "\\usedCities.csv");
	try {
		if (!file)
			throw exception
			("\n\n (!) Ошибка: Файл со списком отыгравших городов - usedCities.csv \n поврежден или отсутствует.\n Переустановите игру.\n\n");
	}
	catch (exception&e) {
		cout << e.what();
		menu(4);
	}
	string str;
	while (!file.eof()) {
		string s;
		getline(file, s);
		//cout << s;
		if (s.size() > 0)
			str = s;
	}
	file.close();

	return str;
}
