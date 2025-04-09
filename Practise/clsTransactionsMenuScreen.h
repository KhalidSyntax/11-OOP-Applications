#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalanceScreen.h";
#include "clsTransferScreen.h";
#include "clsTransfersLogScreen.h";
#include <iomanip>

using namespace std;

class clsTransactionsMenuScreen : protected clsScreen
{
private:

	enum enTransactionsOptions
	{
		eDeposit = 1, eWithdraw = 2,
		eShowTotalBalance = 3, eTransfer = 4,
		eTransferLog = 5, eShowMainMenue = 6
	};

	static short _ReadTransactionsMenuOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 6? ");
		return Choice;
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _ShowDepositScreen()
	{
		// cout << "\nDeposit Screen Will be here...\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		// cout << "\nWithdraw Screen Will be here...\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		// cout << "\nBalances Screen Will be here...\n";
		clsTotalBalanceScreen::ShowTotalBalances();
	}

	static void _ShowTransfer()
	{
		// cout << "\nTransfer Screen Will be here...\n";
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransfersLogScreen()
	{
		// cout << "\nTransfer Screen Will be here...\n";
		clsTransfersLogScreen::ShowTransfersLogScreen();
	}

	static void _PerformTransactionsMenu(enTransactionsOptions TransactionsOptions)
	{
		switch (TransactionsOptions)
		{
		case enTransactionsOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsOptions::eShowTotalBalance:
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsOptions::eTransfer:
			system("cls");
			_ShowTransfer();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsOptions::eTransferLog:
			system("cls");
			_ShowTransfersLogScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsOptions::eShowMainMenue:
			break;
			//do nothing here the main screen will handle it :-) ; 

		}
	}

public:
	static void ShowTransactionsMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menu" << endl;
		cout << setw(37) << left << "" << "============================================\n";

		cout << setw(37) << left << "" << "\t [1] Deposit." << endl;
		cout << setw(37) << left << "" << "\t [2] Withdraw." << endl;
		cout << setw(37) << left << "" << "\t [3] Total Balance." << endl;
		cout << setw(37) << left << "" << "\t [4] Transfer." << endl;
		cout << setw(37) << left << "" << "\t [5] Transfer Log." << endl;
		cout << setw(37) << left << "" << "\t [6] Main Menu." << endl;
		cout << setw(37) << left << "" << "============================================\n";

		_PerformTransactionsMenu((enTransactionsOptions)_ReadTransactionsMenuOptions());
	}
};

