#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsInputValidate.h";
#include"clsUser.h"

class clsAddNewUsersScreen :public clsScreen
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

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo you want to give Full Access? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Client List? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pListClients;

		cout << "\nAdd New Client? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pAddNewClient;

		cout << "\nDelete Client? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pDeleteClient;

		cout << "\nUpdate Client? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pUpdateClients;

		cout << "\nFind Client? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pFindClient;

		cout << "\nTransactions? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pTranactions;

		cout << "\nManage Users? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pManageUsers;

		cout << "\nShow Login Register? y/n? ";
		if (clsInputValidate::ReadYesNo())
			Permissions += clsUser::enPermissions::pShowLoginRegister;

		return Permissions;
	}

	static void _AddNewUser()
	{
		string Username = "";

		cout << "\nPlease Enter User Name: ";
		Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			cout << "\nUser Name is already used, choose another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUser(Username);
		_ReadUserInfo(NewUser);

		clsUser::enSaveResult SaveResult;
		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFailEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;

		case clsBankClient::svSucceeded:
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;

		case clsBankClient::svFaildAccountNumberExist:
			cout << "\nError User was not saved because account number is used!\n";
			break;
		}
	}

	static void _AddNewUsers()
	{
		char AddMore = 'N';
		do
		{
			_AddNewUser();

			cout << "\nUser Added Successfully, Do You Want To Add More Users? Y/N: ";
			cin >> AddMore;

		} while (AddMore == 'Y' || AddMore == 'y');
	}

public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t Add New User Screen");
		_AddNewUsers();
	}
};

