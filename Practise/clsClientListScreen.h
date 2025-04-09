#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include <iomanip>

using namespace std;

class clsClientListScreen: protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }


public:
    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        vector<clsBankClient>vClients = clsBankClient::GetClientsList();

        string Title = "\t Clients List Screen ";
        string SubTitle = "\t (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << setw(15) << left << "Account Number";
        cout << "| " << setw(20) << left << "Client Name";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Pin Code";
        cout << "| " << setw(12) << left << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t No Clients Available In The System!" << endl;
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordLine(C);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

