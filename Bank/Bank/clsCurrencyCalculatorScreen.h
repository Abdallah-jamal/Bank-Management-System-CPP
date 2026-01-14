#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency& Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n______________________________";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code: " << Currency.CurrencyCode();
		cout << "\nCurrency Name: " << Currency.CurrencyName();
		cout << "\nRate         : " << Currency.Rate();
		cout << "\n______________________________\n";
	}

	static float _ReadAmount()
	{
		float Amount = 0;
		cout << "\nPlease enter the amount to Exchange: ";
		cin >> Amount;
		return Amount;
	}

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
		{
			cout << "\nNo Currency found with this Currency Code, enter again: ";
			cin >> CurrencyCode;
		}
		return CurrencyCode;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		_DrawScreenHeader("\t  Currency Calculator Screen");

		cout << "\nPlease enter the Currency Code to Exchange From: ";
		string CurrencyCode = _ReadCurrencyCode();
		clsCurrency FromCurrency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		_PrintCurrencyCard(FromCurrency);


		cout << "\nPlease enter the Currency Code to Exchange To: ";
		string ToCurrencyCode = _ReadCurrencyCode();
		clsCurrency ToCurrency = clsCurrency::FindByCurrencyCode(ToCurrencyCode);
		_PrintCurrencyCard(ToCurrency);

		float Amount = _ReadAmount();

		float ExchangedAmount = FromCurrency.ConvertTo(ToCurrency, Amount);

		cout << "\n----------------------------------------";
		cout << "\nResult:";
		cout << "\n" << Amount << " " << FromCurrency.CurrencyCode()
			<< " = " << ExchangedAmount << " " << ToCurrency.CurrencyCode();
		cout << "\n----------------------------------------\n";
	}
};

