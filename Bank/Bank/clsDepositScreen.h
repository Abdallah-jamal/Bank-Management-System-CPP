#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        string accountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> accountNumber;
        return accountNumber;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string accountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Sorry client with account number [" << accountNumber << "] is not found\n";
            accountNumber = _ReadAccountNumber();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        float amount = 0;
        cout << "\nPlease enter deposit amount? ";
        amount = clsInputValidate::ReadDblNumber();

        cout << "Are you sure to deposit: ";
        char answer = 'y';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            client.Deposit(amount);
            cout << "\nNew Balance: " << client.AccountBalance;
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};

