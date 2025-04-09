#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainMnue.h"  
#include "clsInputValidate.h"
#include "clsDate.h"
#include "Global.h"


class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		string Username, Password;
		bool LoginFailed = false;
		short FaildLoginCount = 0;

		do
		{
			if (LoginFailed)
			{
				FaildLoginCount++;
				cout << "\nInvalid Username/Password! \n";

				cout << "You Have " << (3 - FaildLoginCount) << " Trial(s) To Login\n\n";
				
			}

			if (FaildLoginCount == 3)
			{
				cout << "\n\nYou Are Locked After 3 Failed Trials\n\n";
				return false;
			}

			cout << "Enter Username? ";
			Username = clsInputValidate::ReadString();

			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainMnue::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};
