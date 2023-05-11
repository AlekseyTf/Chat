#include"chat.h"
#include<iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	Chat chat;
	chat.start();
	while (chat.isChatWork())
	{
		chat.showLoginMenu();
		while (chat.getCurrentUser())
		{
			chat.showMenu();
		}
	}



	return 0;
}