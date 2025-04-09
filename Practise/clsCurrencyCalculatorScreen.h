#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";

class clsCurrencyCalculatorScreen :protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency, string Title)
	{
		cout << '\n' << Title << '\n';
		cout << "___________________________________\n\n";
		cout << "Country    : " << Currency.Country() << endl;
		cout << "Code       : " << Currency.CurrencyCode() << endl;
		cout << "Name       : " << Currency.CurrencyName() << endl;
		cout << "Rate (1$)  : " << Currency.Rate() << endl;
		cout << "___________________________________\n\n";
	}

	static void _PrintCalculationToUSD(float Amount, clsCurrency FromCurrency, clsCurrency ToCurrency)
	{
		_PrintCurrency(FromCurrency, "Convert From:");
		float AmountInUSD = FromCurrency.ConvertToUSD(Amount);

		cout << Amount << " " << FromCurrency.CurrencyCode() << " = " <<
			AmountInUSD << " USD" << endl;
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency FromCurrency, clsCurrency ToCurrency)
	{
		if (FromCurrency.CurrencyCode() == ToCurrency.CurrencyCode())
		{
			cout << endl;
			cout << Amount << " " << FromCurrency.CurrencyCode() <<
				" = " << Amount << " " << ToCurrency.CurrencyCode() << endl;
			return;
		}

		if (FromCurrency.CurrencyCode() != "USD")
			_PrintCalculationToUSD(Amount, FromCurrency, ToCurrency);

		if (ToCurrency.CurrencyCode() == "USD")
			return;

		cout << "\n\nConverting From USD To: \n";
		_PrintCurrency(ToCurrency, "Convert To:");

		float ConvertedAmount = FromCurrency.ConvertToOtherCurrency(Amount, ToCurrency);

		cout << Amount << " " << FromCurrency.CurrencyCode() <<
			" = " << ConvertedAmount << " " << ToCurrency.CurrencyCode() << endl;
	}

	static float _ReadAmount()
	{
		cout << "\nEnter Amount To Exchange: ";
		float Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static clsCurrency _GetCurrency(string Message)
	{
		cout << Message;
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency [" << CurrencyCode << "] Was Not Found, Enter Another One: ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		return clsCurrency::FindByCode(CurrencyCode);
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Ans = 'n';
		
		do
		{
			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency SourceCurrency = _GetCurrency("\nEnter Currency 1 Code: ");
			clsCurrency TargetCurrency = _GetCurrency("\nEnter Currency 2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, SourceCurrency, TargetCurrency);

			cout << "\n\nDo You Want To Perform Another Calculation? Y/N: ";
			cin >> Ans;

		} while (Ans == 'Y' || Ans == 'y');
	}
};

