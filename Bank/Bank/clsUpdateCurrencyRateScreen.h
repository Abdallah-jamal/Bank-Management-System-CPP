#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static float _ReadNewRate()
	{
		float NewRate = 0;
		cout << "\nPlease enter the new rate: ";
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrencyCard(clsCurrency& Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n______________________________";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Name: " << Currency.CurrencyName();
		cout << "\nCurrency Code: " << Currency.CurrencyCode();
		cout << "\nRate         : " << Currency.Rate();
		cout << "\n______________________________\n";
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t  Update Currency Rate Screen");

		string CurrencyCode = "";

		cout << "\nPlease enter the Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
		{
			cout << "\nNo Currency found with this Currency Code, enter again: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		char answer = 'y';

		cout << "\nAre you sure you want to update the rate for this currency? (y/n): ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			cout << "\nUpdating Currency Rate...\n";
			cout << "-------------------------\n";
			Currency.UpdateRate(_ReadNewRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nOperation Cancelled :-)\n";
		}
			
	}


};

