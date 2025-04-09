#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h";

using namespace std;

class clsUpdateClientScreen:protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }

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
    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tUpdate client screen");

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

        char Ans = 'n';
        cout << "\n\nAre You Sure Do You Want To Update This Client? Y/N? ";
        cin >> Ans;

        if (Ans == 'y' || Ans == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            _ReadClientInfo(Client1);

            clsBankClient::enSaveResult SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResult::svSucceeded:
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client1);
                break;
            
            case clsBankClient::enSaveResult::svFailEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;

            }
        }
        else
            cout << "\nOperation Canceled, Client Was Not Updated." << endl;
    }
};

