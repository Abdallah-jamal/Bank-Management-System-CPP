#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsPerson.h"

class clsFindUserScreen : protected clsScreen
{
    static void _PrintUser(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.FirstName;
        cout << "\nLastName    : " << user.LastName;
        cout << "\nFull Name   : " << user.FullName();
        cout << "\nEmail       : " << user.Email;
        cout << "\nPhone       : " << user.Phone;
        cout << "\nUserName    : " << user.UserName;
        cout << "\nPassword    : " << user.Password;
        cout << "\nPermissions : " << user.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");

        string userName = "";

        cout << "Please enter the user name: ";
        userName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(userName))
        {
            cout << "Sorry, the user name is not found, try again: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser findUser = clsUser::Find(userName);


        if (!findUser.IsEmpty())
        {
            cout << "\n\nUser Found\n";
            _PrintUser(findUser);
        }
        else
        {
            cout << "Sorry user name is found";
        }

    }
};

