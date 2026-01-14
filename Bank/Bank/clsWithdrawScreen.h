#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string accountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Sorry client with account number [" << accountNumber << "] is not found\n";
            accountNumber = _ReadAccountNumber();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        float amount = 0;
        cout << "\nPlease enter withdraw amount? ";
        amount = clsInputValidate::ReadDblNumber();

        cout << "Are you sure to withdraw: ";
        char answer = 'y';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (client.Withdraw(amount))
            {
                cout << "\nAmount Withdraw Successfylly\n";
                cout << "\nNew Balance: " << client.AccountBalance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << amount;
                cout << "\nYour Balance is: " << client.AccountBalance;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};