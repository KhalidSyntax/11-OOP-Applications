#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";

class clsCurrenciesListScreen :protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(8) << left << Currency.Rate();

	}

public:
    static void ShowCurrenciesList()
    {
        vector<clsCurrency>vCurrencies = clsCurrency::GetCurrencyList();

        string Title = "\t Currencies List Screen ";
        string SubTitle = "\t(" + to_string(vCurrencies.size()) + ") Currency(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << setw(30) << left << "Country";
        cout << "| " << setw(8) << left << "Currency Code";
        cout << "| " << setw(45) << left << "Currency Name";
        cout << "| " << setw(8) << left << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t No Currencies Available In The Sysstem!" << endl;
        else
        {
            for (clsCurrency& C : vCurrencies)
            {
                _PrintCurrencyRecordLine(C);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;
    }

};

