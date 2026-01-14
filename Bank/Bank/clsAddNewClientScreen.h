#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;
 
class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& clientInfo)
	{
		cout << "Enter First Name: ";
		clientInfo.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name: ";
		clientInfo.LastName = clsInputValidate::ReadString();

		cout << "Enter Email: ";
		clientInfo.Email = clsInputValidate::ReadString();

		cout << "Enter Phone: ";
		clientInfo.Phone = clsInputValidate::ReadString();

		cout << "Enter Pin Code: ";
		clientInfo.PinCode = clsInputValidate::ReadString();

		cout << "Enter Account Balance: ";
		clientInfo.AccountBalance = clsInputValidate::ReadFloatNumber();

	}

	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:\n";
		cout << "----------------------------";
		cout << "\nFirst Name     : " << client.FirstName;
		cout << "\nLast Name      : " << client.LastName;
		cout << "\nPhone          : " << client.Phone;
		cout << "\nEmail          : " << client.Email;
		cout << "\nAccount Number : " << client.AccountNumber();
		cout << "\nPin Code       : " << client.PinCode;
		cout << "\nAccount Balance: " << client.AccountBalance;
		cout << "\n----------------------------\n";

	}

public:

	static void ShowAddNewClintScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t  Add New Client Screen");

		string accountNumber = "";

		cout << "Please enter the account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(accountNumber))
		{
			cout << "Sorry the account Number is already existed, try again: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient newClient = clsBankClient::GetAddNewClientObject(accountNumber);

		_ReadClientInfo(newClient);

		clsBankClient::enSaveResults saveResult;

		saveResult = newClient.Save();

		switch (saveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(newClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
		}

	}
};

