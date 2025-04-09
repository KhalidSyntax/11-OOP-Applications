#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";

class clsFindCurrency : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card: ";
		cout << "\n___________________________________\n";
		cout << "\nCountry   : " << Currency.Country() << endl;
		cout << "Code      : " << Currency.CurrencyCode() << endl;
		cout << "Name      : " << Currency.CurrencyName() << endl;
		cout << "Rate (1$) : " << Currency.Rate() << endl;
		cout << "\n___________________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was Not Found.\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");
	
		cout << "\nFind By: [1] Code or [2] Country? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "\nFind By: [1] Code or [2] Country? ");

		if (Choice == 1)
		{
			cout << "\nPlease Enter Currency Code: ";
			string CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
			
		}
		if (Choice == 2)
		{
			cout << "\nPlease Enter Country Name: ";
			string CountryName = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
			_ShowResults(Currency);
		}

	}
};

