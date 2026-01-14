#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.FirstName;
        cout << "\nLastName    : " << user.LastName;
        cout << "\nFull Name   : " << user.FullName();
        cout << "\nEmail       : " << user.Email;
        cout << "\nPhone       : " << user.Phone;
        cout << "\nUser Name   : " << user.UserName;
        cout << "\nPassword    : " << user.Password;
        cout << "\nPermissions : " << user.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\tDelete User Screen");

        string userName = "";

        cout << "Please enter the user name: ";
        userName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(userName))
        {
            cout << "Sorry, the user name is not found, try again: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser user = clsUser::Find(userName);
        _PrintUser(user);

        char answer = 'y';

        cout << "\nAre you sure you want to delete this account: ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            if (user.Delete())
            {
                cout << "\nUser deleted succssfully...";;
                _PrintUser(user);
            }
            else
            {
                cout << "\Error was not deleted";
            }
        }
        else
        {
            cout << "\noperation canceled";
        }

    }

};

