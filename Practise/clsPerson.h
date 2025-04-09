#pragma once

#include <iostream>
#include <string>
#include "InterfaceCommunication.h";

using namespace std;

class clsPerson :public InterfaceCommunication
{

private:
    string _FirstName;
    string _LastName;
    string _Phone;
    string _Email;

public:

    clsPerson(string FirstName, string LastName, string Phone, string Email)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Phone = Phone;
        _Email = Email;
    }

    void setFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string GetFirstName()
    {
        return _FirstName;
    }

    __declspec(property(get = GetFirstName, put = setFirstName))string FirstName;

    void setLastName(string LastName)
    {
        _LastName = LastName;
    }

    string GetLastName()
    {
        return _LastName;
    }

    __declspec(property(get = GetLastName, put = setLastName))string LastName;

    void setEmail(string Email)
    {
        _Email = Email;
    }

    string GetEmail()
    {
        return _Email;
    }

    __declspec(property(get = GetEmail, put = setEmail))string Email;

    void setPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetPhone()
    {
        return _Phone;
    }

    __declspec(property(get = GetPhone, put = setPhone))string Phone;

    string GetFullName()
    {
        return _FirstName + " " + _LastName;
    }
    
    void SendEmail(string Title, string Body)
    {

    }

    void SendFax(string Title, string Body)
    {

    }

    void SendSMS(string Title, string Body)
    {

    }
};
