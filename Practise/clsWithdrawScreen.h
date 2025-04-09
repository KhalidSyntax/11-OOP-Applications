#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";

using namespace std;

class clsWithdrawScreen : protected clsScreen
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
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

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

        cout << "\nPlease Enter Withdraw Amount: ";
        double Amount = clsInputValidate::ReadDblNumber();

        if (Amount > Client1.AccountBalance)
        {
            cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << Client1.AccountBalance << endl;
            cout << "\nAmount Entered: " << Amount << endl;
            return;
        }

        char Ans = 'n';
        cout << "\n\nAre You Sure You Want To Perform This Transaction? Y/N? ";
        cin >> Ans;

        if (Ans == 'y' || Ans == 'Y')
        {
            if (Client1.Withdraw(Amount))
            {
                cout << "\n\nAmount Withdraw Successfully.";
                cout << "New Balance Is : " << Client1.AccountBalance << endl;
            }
            else
            {
                cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client1.AccountBalance;
            }
        }
        else
            cout << "\n\nOperation Canceled. , Amount Was Not Withdraw." << endl;
    }

};

