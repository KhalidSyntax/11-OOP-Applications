#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h";

using namespace std;

class clsFindClientScreen:protected clsScreen
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
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;// this will exit the function and it will not continue
		}

		_DrawScreenHeader("\tFind Client Screen");

		cout << "\nEnter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\nAccount Number Was Not Found, Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (!Client.IsEmpty())
		{
			_PrintClient(Client);
			cout << "\nClient Found." << endl;
		}
		else
			cout << "\nClient Was Not Found." << endl;

	}
};

