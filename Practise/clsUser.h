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

const string UsersFileName = "Users.txt";

class clsUser : public clsPerson
{
private:

	enum enMode
	{
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

	enMode _Mode;
	string _UserName = "";
	string _Password = "";
	int _Permissions = 0;
	bool _MarkForDelete = false;

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += Username + Seperator;
		LoginRecord += clsUtility::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	static clsUser _ConvertLinetoUserObject(string LineRecord, string Separator = "#//#")
	{
		vector <string>vUserData;
		vUserData = clsString::Split(LineRecord, Separator);

		return clsUser(
			enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtility::DecryptionText(vUserData[5]) , stoi(vUserData[6])
		);
	}

	struct  stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLineToRegisteredUser(string LineRecord, string Separator = "#//#")
	{
		vector <string>vLoginRegisterData;
		vLoginRegisterData = clsString::Split(LineRecord, Separator);

		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.Date_Time = vLoginRegisterData[0];
		LoginRegisterRecord.UserName = vLoginRegisterData[1];
		LoginRegisterRecord.Password = clsUtility::DecryptionText(vLoginRegisterData[2]);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterData[3]);

		return LoginRegisterRecord;
	}

	static string _ConverUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += User.FirstName + Separator;
		stClientRecord += User.LastName + Separator;
		stClientRecord += User.Phone + Separator;
		stClientRecord += User.Email + Separator;
		stClientRecord += User.GetUsername() + Separator;
		stClientRecord += clsUtility::EncryptText(User.GetPassword()) + Separator;
		stClientRecord += to_string(User.Permissions);

		return stClientRecord;
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		fstream MyFile;
		vector<clsUser>_vUsers;

		MyFile.open(UsersFileName, ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				_vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _vUsers;
	}

	static void _SaveUserDataToFile(vector<clsUser>& vUser)
	{
		fstream MyFile;

		MyFile.open(UsersFileName, ios::out); // OverWrite

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsUser& U : vUser)
			{
				if (U.MarkForDelete() == false)
				{
					DataLine = _ConverUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsUser>_vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == Username)
			{
				U = *this;
				break;
			}
		}
		_SaveUserDataToFile(_vUsers);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open(UsersFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void _AddNewUser()
	{
		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct  stLoginRegisterRecord
	{
		string Date_Time;
		string UserName;
		string Password;
		int Permissions;
	};

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pShowLoginRegister = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Phone, string Email, string Username, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Phone, Email)
	{
		_Mode = Mode;
		_UserName = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return(_Mode == enMode::EmptyMode);
	}

	bool MarkForDelete()
	{
		return _MarkForDelete;
	}

	void SetUsername(string Username)
	{
		_UserName = Username;
	}

	string GetUsername()
	{
		return _UserName;
	}
	__declspec(property(get = GetUsername, put = SetUsername))string Username;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	static clsUser Find(string Username)
	{

		fstream MyFile;

		MyFile.open(UsersFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.GetUsername() == Username)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;

		MyFile.open(UsersFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.GetUsername() == Username && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
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
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResult::svFaildAccountNumberExist;
			}
			else
			{
				_AddNewUser();
				_Mode = enMode::AddNewMode;
				return enSaveResult::svSucceeded;
			}
		}
	}

	static bool IsUserExist(string Username)
	{
		clsUser User = clsUser::Find(Username);
		return(!User.IsEmpty());
	}

	bool Delete()
	{
		vector<clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == "Admin")
				return false;
			
			if (U.Username == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}
		_SaveUserDataToFile(_vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUser(string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	static vector<clsUser>GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
		{
			return true;
		}

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn()
	{
		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		string DataLine = _PrepareLogInRecord();

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord>GetLoginRegisterList()
	{
		fstream MyFile;
		vector<stLoginRegisterRecord>_vLoggedInUsers;
		stLoginRegisterRecord RegisteredUser;

		MyFile.open("LoginRegister.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				RegisteredUser = _ConvertLineToRegisteredUser(Line);
				_vLoggedInUsers.push_back(RegisteredUser);
			}
			MyFile.close();
		}
		return _vLoggedInUsers;
	}

};

