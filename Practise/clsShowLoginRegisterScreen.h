#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include <iomanip>
#include "clsUser.h";

using namespace std;

class clsShowLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintUserLoginRecord(clsUser::stLoginRegisterRecord LoginedUser)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginedUser.Date_Time;
        cout << "| " << setw(20) << left << LoginedUser.UserName;
        cout << "| " << setw(20) << left << LoginedUser.Password;
        cout << "| " << setw(10) << left << LoginedUser.Permissions;
    }


public:
    static void ShowLoginRegisterList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pShowLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }

        vector<clsUser::stLoginRegisterRecord>vLoggedInUsers = clsUser::GetLoginRegisterList();

        string Title = "\t Login Register List Screen ";
        string SubTitle = "\t\t(" + to_string(vLoggedInUsers.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << setw(35) << left << "Date/Time";
        cout << "| " << setw(20) << left << "UserName";
        cout << "| " << setw(20) << left << "Password";
        cout << "| " << setw(10) << left << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoggedInUsers.size() == 0)
            cout << "\t\t\t No Logins  Available In The Sysstem!" << endl;
        else
        {
            for (clsUser::stLoginRegisterRecord& L : vLoggedInUsers)
            {
                _PrintUserLoginRecord(L);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

