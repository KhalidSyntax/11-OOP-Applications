#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";

class clsUpdateCurrencyRateScreen:protected clsScreen
{
private:

	static float _ReadRate()
	{
		float Rate = 0;
		cout << "\nEnter New Rate: ";
		Rate = clsInputValidate::ReadFloatNumber();
		return Rate;
	}

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

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("     Update Currency Rate Screen");
		
		string CurrencyCode;
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency [" << CurrencyCode << "] Was Not Found, Enter Another One: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre You Sure Do You Want To Updtae The Rate Of This Currency Y/N? ";
		if (clsInputValidate::ReadYesNo())
		{
			cout << "\n\nUpdate Currency Rate:\n";
			cout << "____________________________\n";
		
			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
		else
			cout << "\nOperation Canceled, Currency Rate Was Not Updated." << endl;
	}
};

