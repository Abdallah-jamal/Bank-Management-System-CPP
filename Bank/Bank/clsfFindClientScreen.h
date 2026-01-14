#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsfFindClientScreen : protected clsScreen
{

private:
    static void _PrintClient(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.AccountNumber();
        cout << "\nPassword    : " << client.PinCode;
        cout << "\nBalance     : " << client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        string accountNumber;

        cout << "Please enter the account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Sorry account number is not found, try again: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);

        if (!client.IsEmpty())
        {
            cout << "account number is found :-)\n";
            _PrintClient(client);
        }
        else
        {
            cout << "account number is not fount :-(\n";
        }
    }
};

