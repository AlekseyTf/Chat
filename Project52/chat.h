#pragma once
#include<vector>
#include<exception>
#include<memory>
#include "massege.h"

using namespace std;

class LoginBusy : public exception
{
private:
	const char* what() const noexcept override
	{
		return "Ошибка: этот логин занят!";
	}
};

class NameBusy : public exception
{
private:
	const char* what() const noexcept override
	{
		return "Ошибка: это имя занято!";
	}
};

class Chat
{
private:
	bool _isWork = false;
	vector<User> _userAll;
	vector<Message> _messageAll;
	shared_ptr<User> _currentUser = nullptr;
	
	void login();
	void signUp();
	void showChat() const;
	void showAllUserName() const;
	void addMessage();

	vector<User>& getAllUser()
	{
		return _userAll;
	}
	vector<Message>& getAllMassege()
	{
		return _messageAll;
	}
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;

public:
	void start();
	bool isChatWork() const
	{
		return _isWork;
	}
	shared_ptr<User> getCurrentUser() const
	{
		return _currentUser;
	}
	void showLoginMenu();
	void showMenu();
};