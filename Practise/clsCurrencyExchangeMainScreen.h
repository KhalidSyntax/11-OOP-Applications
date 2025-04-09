#pragma once
#include <iostream>
#include "clsScreen.h";
#include"clsCurrency.h";
#include "clsCurrenciesListScreen.h";
#include "clsInputValidate.h";
#include "clsFindCurrency.h";
#include "clsUpdateCurrencyRateScreen.h";
#include "clsCurrencyCalculatorScreen.h";
#include <iomanip>

using namespace std;

class clsCurrencyExchangeMainScreen :protected clsScreen
{
private:

	enum enManageCurrenciesMenuOptions
	{
		eCurrencyList = 1, eFindCurrency = 2,
		eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5
	};

	static short _ReadCurrenciesMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number Between 1 to 5? ");
		return Choice;
	}

	static void _GoBackToCurrenciesMenuScreen()
	{
		cout << "\n\n\nPress Any Key To Go Back To Currency Exchange Menu...";
		system("pause>0");
		ShowCurrencyExchangeMenu();
	}

	static void _ShowCurrencyListScreen()
	{
		// cout << "\nCurrency List Screen Will Be Here...";
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _ShowFindCurrencyScreen()
	{
		// cout << "\nFind Currency Screen Will Be Here...";
		clsFindCurrency::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		// cout << "\nUpdate Currency Screen Will Be Here...";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		// cout << "\nCurrency Calculator Screen Will Be Here...";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMenuOption(enManageCurrenciesMenuOptions ManageUsersMenuOptions)
	{
		switch (ManageUsersMenuOptions)
		{
		case enManageCurrenciesMenuOptions::eCurrencyList:
			system("cls");
			_ShowCurrencyListScreen();
			_GoBackToCurrenciesMenuScreen();
			break;

		case enManageCurrenciesMenuOptions::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenuScreen();
			break;

		case enManageCurrenciesMenuOptions::eUpdateRate:
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenuScreen();
			break;

		case enManageCurrenciesMenuOptions::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenuScreen();
			break;

		case enManageCurrenciesMenuOptions::eMainMenu:
			break;
			//do nothing here the main screen will handle it :-) 
		}
	}

public:
	static void ShowCurrencyExchangeMenu()
	{

		system("cls");
		_DrawScreenHeader("   Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
		cout << setw(37) << left << "" << "========================================\n";

		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "========================================\n";
		_PerformCurrenciesMenuOption((enManageCurrenciesMenuOptions)_ReadCurrenciesMenuOption());
	}
};

