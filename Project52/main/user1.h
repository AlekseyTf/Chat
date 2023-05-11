#pragma once

#include<string>
using namespace std;

class User
{
private:
	const string _login;
	string _pass;
	string _name;

public:
	User(const string& login, const string& name, const string& pass) : _login(login), _name(name), _pass(pass)
	{

	}
	const string& getLogin()
	{
		return _login;
	}
	const  string& getName()
	{
		return _name;
	}
	const string& getPass()
	{
		return _pass;
	}
	void setName(const string& name)
	{
		_name = name;
	}
	void setPass(const string& pass)
	{
		_pass = pass;
	}
};


