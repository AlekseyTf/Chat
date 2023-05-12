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
		cout << "Ëîãèí: ";
		cin >> login;
		cout << "Ïàðîëü: ";
		cin >> pass;

		_currentUser = getUserByLogin(login);

		if (_currentUser == nullptr || (pass != _currentUser->getPass()))
		{
			_currentUser = nullptr;

			cout << "Îøèáêà: íåò òàêîãî ëîãèíà " << endl;
			cout << " Q - äëÿ âûõîäà èëè ëþáóþ êëàâèøó äëÿ ïðîäîëæåíèÿ ";
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

	cout << "Ëîãèí: ";
	cin >> login;
	cout << "Èìÿ: ";
	cin >> name;
	cout << "Ïàðîëü: ";
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
		//Ïîêàçûâàåò ñîîáùåíèÿ äëÿ òåêóùåãî ïîëüçîâàòåëÿ äëÿ íåãî è äëÿ âñåõ.
		//if (_currentUser->getUserLogin() == message.getFrom() || _currentUser->getUserLogin() == message.getTo() || message.getTo() == "all")
		{
			//ïîäìåíÿåì äëÿ ñåáÿ èìÿ íà me
			from = (_currentUser->getUserLogin() == message.getFrom()) ? "ÿ" : getUserByLogin(message.getFrom())->getUserName();
			if (message.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (_currentUser->getUserLogin() == message.getTo()) ? "ÿ" : getUserByLogin(message.getTo())->getUserName();
			}
			cout << "Ñîîáùåíèå îò " << from << " äëÿ " << to << endl;
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
		cout  << "  1 - Âîéòè  \t2 - Ðåãèñòðàöèÿ \tQ - Âûõîä" << endl;
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

	cout << "Ñîîáùåíèå äëÿ (îòïðàâèòü âñåì - all):_";
	cin >> to;
	cout << "Òåêñò: " << endl;;
	cin.ignore();
	getline(cin, text);

	if (!(to == "all" || getUserByName(to)))// åñëè íå óäàëîñü íàéòè ïîëó÷àòåëÿ ïî èìåíè
	{
		cout << "Îøèáêà: íåò òàêîãî ïîëüçîâàòåëÿ " << to << endl;
		return;
	}
	else
	{
		cout << "Ñîîáùåíèå îòïðàâëåíî!!" << endl;
	}
	if (to == "all")
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  "all", text });
	else
		_messageAll.push_back(Message{ _currentUser->getUserLogin(),  getUserByName(to)->getUserLogin(), text });
}

void Chat::showMenu()
{
	char operation;

	cout << "Ïðèâåò!!" << _currentUser->getUserName() << endl;

	while (_currentUser)
	{
		cout << "*****************************************************************" << endl;
		cout << " 1 - ×àò | 2 - Íàïèñàòü ñîîáùåíèå | 3 - Ïîëüçîâàòåëè | Q - Âûõîä " << endl;
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
			cout << "Îøèáêà: âûáîðà, ñïðîáóéòå ùå" << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "**************************Ïîëüçîâàòåëè**************************" << endl;

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
