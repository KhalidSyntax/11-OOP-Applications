#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsListUsersScreen.h";
#include "clsAddNewUsersScreen.h";
#include "clsDeleteUserScreen.h";
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";
#include <iomanip>

using namespace std;

class clsManageUsersMenuScreen : protected clsScreen
{
private:
	enum enManageUsersMenuOptions
	{
		eListUsers = 1, eAddNewUser = 2,
		eDeleteUser = 3, eUpdateUser = 4,
		eFindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 6? ");
		return Choice;
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowManageUsersMenuOptions();
	}

	static void _ShowListUsersScreen()
	{
		// cout << "\nList Users will be here...\n";
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUsersScreen()
	{
		// cout << "\nAdd New Users will be here...\n";
		clsAddNewUsersScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		// cout << "\nDelete Users will be here...\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		// cout << "\nUpdate Users will be here...\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		// cout << "\nFind Users will be here...\n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenuOptions(enManageUsersMenuOptions ManageUsersMenuOptions)
	{
		switch (ManageUsersMenuOptions)
		{
		case enManageUsersMenuOptions::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenu();
			break;

		case enManageUsersMenuOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUsersScreen();
			_GoBackToManageUsersMenu();
			break;

		case enManageUsersMenuOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enManageUsersMenuOptions::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enManageUsersMenuOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enManageUsersMenuOptions::eMainMenue:
			break;
			//do nothing here the main screen will handle it :-) ; 
		}
	}

public:
	static void ShowManageUsersMenuOptions()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Screen\n";
		cout << setw(37) << left << "" << "========================================\n";

		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "========================================\n";
		_PerformManageUsersMenuOptions((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}
};

