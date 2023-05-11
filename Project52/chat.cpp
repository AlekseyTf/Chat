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
		cout << "�����: ";
		cin >> login;
		cout << "������: ";
		cin >> pass;

		_currentUser = getUserByLogin(login);

		if (_currentUser == nullptr || (pass != _currentUser->getPass()))
		{
			_currentUser = nullptr;

			cout << "������: ��� ������ ������ " << endl;
			cout << " Q - ��� ������ ��� ����� ������� ��� ����������� ";
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

	cout << "�����: ";
	cin >> login;
	cout << "���: ";
	cin >> name;
	cout << "������: ";
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
		//���������� ��������� ��� �������� ������������ ��� ���� � ��� ����.
		//if (//_currentUser->getUserLogin() == messade.getFrom() )//|| _currentUser->getUserLogin() == message.getTo() ||(
		if (	message.getTo() == "all")
		{
			//��������� ��� ���� ��� �� me
			from = (_currentUser->getUserLogin() == message.getFrom()) ? "�" : getUserByLogin(message.getFrom())->getUserName();
			if (message.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (_currentUser->getUserLogin() == message.getTo()) ? "�" : getUserByLogin(message.getTo())->getUserName();
			}
			cout << "��������� �� " << from << " ��� " << to << endl;
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
		cout  << "  1 - �����  \t2 - ����������� \tQ - �����" << endl;
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

	cout << "��������� ��� (��������� ���� - all):_";
	cin >> to;
	cout << "�����: " << endl;;
	cin.ignore();
	getline(cin, text);

	if (!(to == "all" || getUserByName(to)))// ���� �� ������� ����� ���������� �� �����
	{
		cout << "������: ��� ������ ������������ " << to << endl;
		return;
	}
	else
	{
		cout << "��������� ����������!!" << endl;
	}
	if (to == "all")
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  "all", text });
	else
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  getUserByName(to)->getUserLogin(), text });
}

void Chat::showMenu()
{
	char operation;

	cout << "������!!" << _currentUser->getUserName() << endl;

	while (_currentUser)
	{
		cout << "*****************************************************************" << endl;
		cout << " 1 - ��� | 2 - �������� ��������� | 3 - ������������ | Q - ����� " << endl;
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
			cout << "������: ������, ��������� ��" << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "**************************������������**************************" << endl;

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
