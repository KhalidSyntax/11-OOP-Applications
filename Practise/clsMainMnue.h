#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsClientListScreen.h";
#include "clsAddNewClientsScreen.h";
#include "clsDeleteClientScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionsMenuScreen.h";
#include "clsManageUsersMenuScreen.h";
#include "clsShowLoginRegisterScreen.h";
#include "clsCurrencyExchangeMainScreen.h";
#include "clsUser.h";
#include "Global.h";
#include <iomanip>

using namespace std;

class clsMainMnue : protected clsScreen
{
private:
	enum enMainMenuOptions
	{
		eListClients = 1, eAddNewClient = 2,
		eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eLoginRegister = 8,
		eCurrencyExchange = 9, eExit = 10
	};

	static short _ReadMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number Between 1 to 10? ");
		return Choice;
	}

	static void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "\n\tPress any key to go back to Main Menu...";
		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		// cout << "\nClient List Screen Will be here...\n";
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		// cout << "\nAdd New Client Screen will be here...\n";
		clsAddNewClientsScreen::_AddNewClients();
	}

	static void _ShowDeleteClientScreen()
	{
		// cout << "\nDelete Client Screen will be here...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		// cout << "\nUpdate Client Screen will be here...\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		// cout << "\nFind Client Screen will be here...\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		// cout << "\nTransactions Menu will be here...\n";
		clsTransactionsMenuScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenuOptions()
	{
		// cout << "\nUsers Menu will be here...\n";
		clsManageUsersMenuScreen::ShowManageUsersMenuOptions();
	}

	//static void _ShowEndScreen()
	//{
	//	cout << "\nEnd Screen Will be here...\n";

	//}

	static void _ShowLoginRegisterList()
	{
		// cout << "\nLogin Register List will be here...\n";
		clsShowLoginRegisterScreen::ShowLoginRegisterList();
	}

	static void _ShowCurrencyExchange()
	{
		// cout << "\nCurrency Exchange will be here...\n";
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenu();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOptions)
	{
		switch (MainMenuOptions)
		{
		case enMainMenuOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenuOptions();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterList();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchange();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::eExit:
			system("cls");
			_Logout();
			break;
		}
	}

public:
	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen", "");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t [1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t [2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t [3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t [4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t [5] Find Client.\n";
		cout << setw(37) << left << "" << "\t [6] Transactions.\n";
		cout << setw(37) << left << "" << "\t [7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t [8] Login Register.\n";
		cout << setw(37) << left << "" << "\t [9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t [10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		
		_PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}

};

