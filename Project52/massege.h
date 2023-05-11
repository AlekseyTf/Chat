#pragma once
#include"user.h"

using namespace std;

class Message
{
private:
	const string _to;
	const string _from;
	const string _text;
public:
	Message(const string& to, const string& from, const string& text) : _to(to), _from(from), _text(text)
	{

	}

	const  string& getTo() const
	{
		return _to;
	}
	const string& getFrom() const
	{
		return _from;
	}
	const string& getText() const
	{
		return _text;
	}
};