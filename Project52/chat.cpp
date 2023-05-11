#include<iostream>
#include"chat.h"

using namespace std;

void Chat::start()
{
	_isWork = true;
}



void Chat::login()
{
	string login;
	string pass;
	char operation;

	do
	{
		cout << "Логин: ";
		cin >> login;
		cout << "Пароль: ";
		cin >> pass;

		_currentUser = getUserByLogin(login);

		if (_currentUser == nullptr || (pass != _currentUser->getPass()))
		{
			_currentUser = nullptr;

			cout << "Ошибка: нет такого логина " << endl;
			cout << " Q - для выхода или любую клавишу для продолжения ";
			cin >> operation;
			if (operation == 'q')
				break;
		}
	} while (!_currentUser);
}

void Chat::signUp()
{
	string login;
	string name;
	string pass;

	cout << "Логин: ";
	cin >> login;
	cout << "Имя: ";
	cin >> name;
	cout << "Пароль: ";
	cin >> pass;

	if (getUserByLogin(login) || login == "all")
	{
		throw LoginBusy();
	}

	if (getUserByName(name) || name == "all")
	{
		throw NameBusy();
	}

	User user = User(login, name, pass);
	_userAll.push_back(user);
	_currentUser = make_shared<User>(user);

}

void Chat::showChat() const
{
	string from;
	string to;
	cout << "*****************************************************************" << endl;

	for (auto& message : _messageAll)
	{
		//Показывает сообщения для текущего пользователя для него и для всех.
		//if (//_currentUser->getUserLogin() == messade.getFrom() )//|| _currentUser->getUserLogin() == message.getTo() ||(
		if (	message.getTo() == "all")
		{
			//подменяем для себя имя на me
			from = (_currentUser->getUserLogin() == message.getFrom()) ? "я" : getUserByLogin(message.getFrom())->getUserName();
			if (message.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (_currentUser->getUserLogin() == message.getTo()) ? "я" : getUserByLogin(message.getTo())->getUserName();
			}
			cout << "Сообщение от " << from << " для " << to << endl;
		}
 	}
	cout << "*****************************************************************" << endl;
}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;

	do
	{
		cout << "*****************************************************************" << endl;
		cout  << "  1 - Войти  \t2 - Регистрация \tQ - Выход" << endl;
		cout << "*****************************************************************" << endl;
		cout << "> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const exception& ex)
			{
				cout << ex.what() << endl;
			}
			break;
		case 'q':
			_isWork = false;
			break;
		default:
			cout << "1 or 2 " << endl;
			break;
		}
	} while (!_currentUser && _isWork);
}

void Chat::addMessage()
{
	string to, text;

	cout << "Сообщение для (отправить всем - all):_";
	cin >> to;
	cout << "Текст: " << endl;;
	cin.ignore();
	getline(cin, text);

	if (!(to == "all" || getUserByName(to)))// если не удалось найти получателя по имени
	{
		cout << "Ошибка: нет такого пользователя " << to << endl;
		return;
	}
	else
	{
		cout << "Сообщение отправлено!!" << endl;
	}
	if (to == "all")
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  "all", text });
	else
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  getUserByName(to)->getUserLogin(), text });
}

void Chat::showMenu()
{
	char operation;

	cout << "Привет!!" << _currentUser->getUserName() << endl;

	while (_currentUser)
	{
		cout << "*****************************************************************" << endl;
		cout << " 1 - Чат | 2 - Написать сообщение | 3 - Пользователи | Q - Выход " << endl;
		cout << "*****************************************************************" << endl;
		cout << "> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUserName();
			break;
		case 'q':
			_currentUser = nullptr;
			break;
		default:
			cout << "Ошибка: выбора, спробуйте ще" << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "**************************Пользователи**************************" << endl;

	for (auto& user : _userAll)
	{
		cout << user.getUserName();

		if (_currentUser->getUserLogin() == user.getUserLogin())
			cout << "(me)" << endl;
	}
	cout << "*****************************************************************" << endl;
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto& user : _userAll)
	{
		if (login == user.getUserLogin())
		{
			return make_shared<User>(user);
		}
	}
	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user : _userAll)
	{
		if (name == user.getUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}
