#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";

using namespace std;

class clsDepositScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_________________\n";
        cout << "\nFirst Name: " << Client.FirstName;
        cout << "\nLast Name : " << Client.LastName;
        cout << "\nFull Name : " << Client.GetFullName();
        cout << "\nPhone     : " << Client.Phone;
        cout << "\nEmail     : " << Client.Email;
        cout << "\nAccount NO: " << Client.GetAccountNumber();
        cout << "\nBalance   : " << Client.AccountBalance;
        cout << "\nPassword  : " << Client.PinCode;
        cout << "\n_________________\n";
    }

public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nPlease Enter Deposit Amount: ";
        double Amount = clsInputValidate::ReadDblNumber();

        char Ans = 'n';
        cout << "\n\nAre You Sure You Want To Perform This Transaction? Y/N? ";
        cin >> Ans;

        if (Ans == 'y' || Ans == 'Y')
        {
            Client1.Deposit(Amount);
            cout << "\n\nAmount Deposited Successfully.";
            cout << "New Balance Is : " << Client1.AccountBalance << endl;
        }
        else
            cout << "\n\nOperation Canceled. , Amount Was Not Deposited." << endl;
    }
};

