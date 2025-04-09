#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h";
#include "clsString.h";
#include "clsDate.h";
#include "clsUtility.h";

using namespace std;

const string ClientFileName = "Clients.txt";

class clsBankClient :public clsPerson
{
private:

	enum enMode
	{
		EmptyMode = 0, UpdateMode = 1, AddNewMode
	};

	enMode _Mode;

	string _AccountNmuber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	string _TranferLogRecordLine(clsBankClient DestinationClient, double Amount, string Username, string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += GetAccountNumber() + Seperator;
		LoginRecord += DestinationClient.GetAccountNumber() + Seperator;
		LoginRecord += to_string(Amount) + Seperator;
		LoginRecord += to_string(AccountBalance) + Seperator;
		LoginRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		LoginRecord += Username;

		return LoginRecord;
	}

	void _RegisterTransfer(clsBankClient DestinationClient, double Amount, string Username)
	{
		_AddDataLineToFile(_TranferLogRecordLine(DestinationClient, Amount, Username), "TransferLogIn.txt");
	}

	struct  stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string LineRecord, string Separator = "#//#")
	{
		vector <string>vTrnsferLogRecordLine;
		vTrnsferLogRecordLine = clsString::Split(LineRecord, Separator);

		stTransferLogRecord TrnsferLogRecord;

		TrnsferLogRecord.Date_Time = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string LineRecord, string Separator = "#//#")
	{
		vector <string>vClientData;
		vClientData = clsString::Split(LineRecord, Separator);

		return clsBankClient(
			enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], clsUtility::DecryptionText(vClientData[5]), stof(vClientData[6])

		);
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Separator;
		stClientRecord += Client.LastName + Separator;
		stClientRecord += Client.Phone + Separator;
		stClientRecord += Client.Email + Separator;
		stClientRecord += Client.GetAccountNumber() + Separator;
		stClientRecord += Client.PinCode + Separator;
		stClientRecord += clsUtility::EncryptText(Client.PinCode) + Separator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector<clsBankClient> _LoadDataFromFileToObject()
	{
		fstream MyFile;
		vector<clsBankClient>_vClients;

		MyFile.open(ClientFileName, ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				_vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _vClients;
	}

	static void _SaveClientDataToFile(vector<clsBankClient>& vClient)
	{
		fstream MyFile;

		MyFile.open(ClientFileName, ios::out); // OverWrite

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClient)
			{
				if (C.MarkForDelete() == false)
				{
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadDataFromFileToObject();

		for (clsBankClient& C : _vClient)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDataToFile(_vClient);
	}

	void _AddDataLineToFile(string stClients, string FileName)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stClients << endl;

			MyFile.close();
		}
	}

	void _AddNewClient()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this), ClientFileName);
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	
	struct  stTransferLogRecord
	{
		string Date_Time;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double srcBalanceAfter;
		double destBalanceAfter;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Phone, string Email, string AccountNumber, string PinCode, double AccountBalance) :
		clsPerson(FirstName, LastName, Phone, Email)
	{
		_Mode = Mode;
		_AccountNmuber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return(_Mode == enMode::EmptyMode);
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient)
	{
		if (_AccountNmuber == DestinationClient.GetAccountNumber())
			return false;

		/*if (Amount > AccountBalance)
			return false;*/

		if (Withdraw(Amount))
		{
			DestinationClient.Deposit(Amount);
			_RegisterTransfer(DestinationClient, Amount, CurrentUser.Username);
			return true;
		}

		return false;
	}

	bool MarkForDelete()
	{
		return _MarkForDelete;
	}

	string GetAccountNumber()
	{
		return _AccountNmuber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance() 
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))double AccountBalance;

	// No UI Related Code inside object
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n_________________\n";
		cout << "\nFirst Name: " << FirstName;
		cout << "\nLast Name : " << LastName;
		cout << "\nFull Name : " << GetFullName();
		cout << "\nPhone     : " << Phone;
		cout << "\nEmail     : " << Email;
		cout << "\nAccount NO: " << _AccountNmuber;
		cout << "\nBalance   : " << _AccountBalance;
		cout << "\nPassword  : " << _PinCode;
		cout << "\n_________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		//vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open(ClientFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				//vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		clsBankClient Client = Find(AccountNumber);
		if (Client.PinCode == PinCode)
		{
			return Client;
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResult { svFailEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResult::svFailEmptyObject;
			}
			
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
		}

		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNmuber))
			{
				return enSaveResult::svFaildAccountNumberExist;
			}
			else
			{
				_AddNewClient();
				_Mode = enMode::AddNewMode;
				return enSaveResult::svSucceeded;
			}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return(!Client.IsEmpty());
	}

	bool Delete()
	{
		vector<clsBankClient> _vClient;
		_vClient = _LoadDataFromFileToObject();

		for (clsBankClient& C : _vClient)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(_vClient);
		*this = _GetEmptyClientObject();
		return true;
	}

	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient>GetClientsList()
	{
		return _LoadDataFromFileToObject();
	}
	
	static double GetTotalBalance()
	{
		vector<clsBankClient>vClients = GetClientsList();
		double TotalBalance = 0;

		for (clsBankClient& C : vClients)
		{
			TotalBalance += C.AccountBalance;
		}
		return TotalBalance;
	}

	static vector<stTransferLogRecord>GetTransfersLogList()
	{
		fstream MyFile;
		vector<stTransferLogRecord>vTransferLogRecord;
		stTransferLogRecord TransferRecord;

		MyFile.open("TransferLogIn.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferLogRecord;
	}

};