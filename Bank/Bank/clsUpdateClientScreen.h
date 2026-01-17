# pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen

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

    static void _ReadClientInfo(clsBankClient& client)
    {
        cout << "\nEnter FirstName: ";
        client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:


    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        _DrawScreenHeader("\tUpdate Client Screen");

        string accountNumber = "";

        cout << "Please enter the account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Sorry the account number is not found, try again: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        cout << "Are you sure to update this client: ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            cout << "\n\nUpdate Client Info\n";
            cout << "____________________\n";

            _ReadClientInfo(client);
        }
        else
        {
               cout << "\n\nClient update canceled....\n";
               return;
        }

        clsBankClient::enSaveResults saveResult;

        saveResult = client.Save();

        switch (saveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "Client updated successfully....\n";
            _PrintClient(client);
            break;

        case clsBankClient::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }

};
