#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumer()
    {
        string accountNumber = "";

        cout << "Please enter account number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, enter again: ";
            accountNumber = clsInputValidate::ReadString();
        }

        return accountNumber;
    }

    static float _ReadAmount(clsBankClient sourceClient)
    {
        float amount = 0;

        cout << "\nPlease enter amount to transfer: ";
        amount = clsInputValidate::ReadFloatNumber();

        while (sourceClient.AccountBalance < amount)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            amount = clsInputValidate::ReadDblNumber();
        }

        return amount;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient sourceClient = clsBankClient::Find(_ReadAccountNumer());

        _PrintClient(sourceClient);

        clsBankClient destinationClient = clsBankClient::Find(_ReadAccountNumer());

        _PrintClient(destinationClient);

        float amount = _ReadAmount(sourceClient);

        char answer = 'n';
        cout << "\nAre you sure you want to perform this operation? y/n: ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (sourceClient.TransferTo(amount, destinationClient, currentUser.UserName))
            {
                cout << "\nTransfer operation completed successfully.\n";

            }
            else
            {
                cout << "\nError: Transfer operation failed.\n";
            }
        }

        _PrintClient(sourceClient);
		_PrintClient(destinationClient);
    }
};
