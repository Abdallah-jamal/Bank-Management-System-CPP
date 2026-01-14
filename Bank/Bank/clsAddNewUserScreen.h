#pragma once

#include <iostream>
#include "clsUser.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& user)
    {
        cout << "\nEnter FirstName: ";
        user.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        user.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        user.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        user.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        user.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        user.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser &user)
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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

		cout << "\nLogin Register? y/n? ";
		cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
			Permissions += clsUser::enPermissions::pLogInRegister;
        }

		cout << "\nCurrency Exchange? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
			Permissions += clsUser::enPermissions::pCurrencyExchange;
        }

        return Permissions;

    }

public:

    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t  Add New User Screen");

        string userName = "";

        cout << "Please enter the user name: ";
        userName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(userName))
        {
            cout << "Sorry, User name is already used, try again: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser newUser = clsUser::GetAddNewUserObject(userName);

        _ReadUserInfo(newUser);

        clsUser::enSaveResults saveResult;

        saveResult = newUser.Save();

        switch (saveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(newUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
};

