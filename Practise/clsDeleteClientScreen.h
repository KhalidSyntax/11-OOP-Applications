#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h";

using namespace std;

class clsDeleteClientScreen: protected clsScreen
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
	static void ShowDeleteClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found please choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        
        char Ans = 'n';

        cout << "\nAre you sure do you want to delete this client? y/n ";
        cin >> Ans;

        if (Ans == 'y' || Ans == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted successfully :-) \n";
                _PrintClient(Client);
            }
        }
        else
        {
            cout << "\nError Client was not Deleted\n";
        }
	}
};

