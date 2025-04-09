#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsInputValidate.h";
#include"clsUser.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.GetFullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.Username;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t Delete User Screen");

        string Username = "";

        cout << "\nPlease Enter User Name: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUser Name is not found [" << Username << "] please choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(Username);
        _PrintUser(User);

        cout << "\nAre You Sure You Want To Delete This User? Y/N: ";
        if (clsInputValidate::ReadYesNo())
        {
            if (Username == "Admin")
            {
                cout << "\nSorry You Cannot Delete This User.";
                return;
            }

            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully." << endl;
                _PrintUser(User);
            }
            else
                cout << "\nError, User Was Not Deleted." << endl;
        }
        else
            cout << "\nOperation Canceled, User Was Not Deleted." << endl;
    }
};