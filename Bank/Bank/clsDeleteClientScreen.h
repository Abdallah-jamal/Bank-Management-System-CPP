#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\tDelete Client Screen");

        string accountNumber = "";

        cout << "Please enter the account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Sorry account number is not fount, try again: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {


            if (client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};

