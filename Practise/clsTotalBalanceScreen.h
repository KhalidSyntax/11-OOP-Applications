#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsUtility.h";
#include <iomanip>

using namespace std;

class clsTotalBalanceScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(40) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

public:
    static void ShowTotalBalances()
    {
        vector<clsBankClient>vClients = clsBankClient::GetClientsList();

        string Title = "\t Balances List Screen";
        string Subtitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, Subtitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;
        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalance = clsBankClient::GetTotalBalance();

        if (vClients.size() == 0)
        {
            cout << clsUtility::Tabs(4) << " No Clients Available In The System!";
            return;
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordBalanceLine(C);
                cout << endl;
            }
        }
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalances = clsBankClient::GetTotalBalance();
        cout << "\n\t\t\t\t\t TotalBalances = " << TotalBalances << endl;
        cout << "\n\t\t\t\t ( " << clsUtility::NumberToText(TotalBalances) << ")" << endl;
    }
};

