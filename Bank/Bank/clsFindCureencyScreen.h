#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;


class clsFindCureencyScreen : protected clsScreen
{
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

	enum enFindCurrencyBy { eByCountry = 1, eByCurrencyCode = 2 };

	static short _ReadFindCurrencyByOption()
	{
		short choice = 0;

		cout << "\nFind Currency By: \n";
		cout << "\t[1] Country.\n";
		cout << "\t[2] Currency Code.\n";
		cout << "\nChoose Option [1 to 2]: ";
		cin >> choice;

		return choice;
	}

	static string _ReadCountryName()
	{
		string CountryName = "";
		cout << "\nPlease enter the Country Name: ";
		CountryName = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCountry(CountryName);

		while (Currency.IsEmpty())
		{
			cout << "\nNo Currency found with this Country Name, enter again: ";
			CountryName = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCountry(CountryName);
		}

		return CountryName;
	}

	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		cout << "\nPlease enter the Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);

		while (Currency.IsEmpty())
		{
			cout << "\nNo Currency found with this Currency Code, enter again: ";
			CurrencyCode = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		}
		return CurrencyCode;
	}

	static clsCurrency _FindCurrency(enFindCurrencyBy FindCurrencyBy)
	{
		clsCurrency Currency;
		switch (FindCurrencyBy)
		{
		case enFindCurrencyBy::eByCountry:
		{
			string CountryName = _ReadCountryName();
			Currency = clsCurrency::FindByCountry(CountryName);
			break;
		}
		case enFindCurrencyBy::eByCurrencyCode:
		{
			string CurrencyCode = _ReadCurrencyCode();
			Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
			break;
		}
		}

		return Currency;
	}

public:

	static void ShowFindCurrencyScreen()
	{
		char answer = 'n';
		_DrawScreenHeader("\t  Find Currency Screen");

		do
		{

			short FindCurrencyByOption = _ReadFindCurrencyByOption();

			clsCurrency Currency = _FindCurrency((enFindCurrencyBy)FindCurrencyByOption);


			cout << "\nCurrency Found Successfully :-)\n";
			_PrintCurrencyCard(Currency);

			cout << "\n\nDo you want to find another currency? (y/n): ";
			cin >> answer;

		} while (answer == 'y' || answer == 'Y');
		
	}
};

