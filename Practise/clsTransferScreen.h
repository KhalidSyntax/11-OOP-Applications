#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsInputValidate.h";
#include"clsUser.h"
#include "clsBankClient.h";

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_________________\n";
        cout << "\nFull Name : " << Client.GetFullName();
        cout << "\nAccount NO: " << Client.GetAccountNumber();
        cout << "\nBalance   : " << Client.AccountBalance;
        cout << "\n_________________\n";
    }

	static string _ReadAccountNumber(string Message)
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number to Transfer " << Message << ": ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\nAccount Number Is Not Found, Enter Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient& SourceClient)
	{
		double Amount = 0;
		cout << "\nEnter Transfer Amount To Transfer? ";
		Amount = clsInputValidate::ReadDblNumber();


		while (Amount > SourceClient.AccountBalance || Amount <= 0)
		{
			if (Amount <= 0)
			{
				cout << "\nAmount Must Be Greater Than Zero. Please Enter Another Amount: " << endl;
				Amount = clsInputValidate::ReadDblNumber();
			}
			cout << "\nAmount Exceeds The Available Balance, Enter Transfer Amount: ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("From"));
		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));

		if (SourceClient.GetAccountNumber() == DestinationClient.GetAccountNumber())
		{
			cout << "\n\nError: You Cannot Transfer Money To Yourself." << endl;
			return;
		}

		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		cout << "\n\nAre You Sure You Want To Perform This Operation? Y/N? ";
		if (clsInputValidate::ReadYesNo())
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				cout << "\n\nAmount Transfered Successfully" << endl;
				_PrintClientCard(SourceClient);
				_PrintClientCard(DestinationClient);
			}
			else
				cout << "\n\nTransfer Failed. Please Try Again Later." << endl;;
		}
		else
			cout << "\n\nOperation Canceled." << endl;

	}
};

