#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsInputValidate.h";
#include"clsUser.h"

class clsFindUserScreen:protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.GetFullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.Username;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");

		cout << "\nEnter User Name: ";
		string Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\n\nUser [" << Username << "] Was Not Found, Enter Another One : ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		if (!User.IsEmpty())
		{
			cout << "\nUser Found." << endl;
			_PrintUser(User);
		}
		else
			cout << "\nUser Was Not Found." << endl;
	}

};

