#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"

class clsListUsersScreen:protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << User.GetUsername();
        cout << "| " << setw(25) << left << User.GetFullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;
    }

public:
    static void ShowUsersList()
    {
        vector<clsUser>vUsers = clsUser::GetUsersList();

        string Title = "\t Users List Screen ";
        string SubTitle = "\t (" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << setw(12) << left << "User Name";
        cout << "| " << setw(25) << left << "Full Name";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(12) << left << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {
            for (clsUser& U : vUsers)
            {
                _PrintUserRecordLine(U);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;
    }

};

