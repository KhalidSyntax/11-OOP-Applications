#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
#include <iomanip>

using namespace std;

class clsAddNewClientsScreen :protected clsScreen
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

	static void _AddNewClient()
	{
		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is already used, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);
		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFailEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;

		case clsBankClient::svSucceeded:
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::svFaildAccountNumberExist:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
	}

public:
	static void _AddNewClients()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;// this will exit the function and it will not continue
		}

		_DrawScreenHeader("\tAdd New Client Screen");
		_AddNewClient();
	}

};

