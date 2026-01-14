#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static void _Login()
	{
		string userName = "", password = "";

		bool LoginFailed = false;
		short Attempts = 0;
		do {

			if (LoginFailed)
			{
				cout << "\nIncorrect UserName/Password, please try again.\n";
				Attempts++;
			}

			if (Attempts == 3)
			{
				cout << "\nYou have exceeded the maximum number of login attempts.\n";
				exit(0);
			}

			
			cout << "\nPlease enter UserName: ";
			userName = clsInputValidate::ReadString();
			cout << "\nPlease enter Password: ";
			password = clsInputValidate::ReadString();

			clsUser user = clsUser::Find(userName, password);

			LoginFailed = user.IsEmpty();

			if (!LoginFailed)
			{
				currentUser = user; 
			}

		} while (LoginFailed);

		currentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}

public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		_Login();
	}
};

