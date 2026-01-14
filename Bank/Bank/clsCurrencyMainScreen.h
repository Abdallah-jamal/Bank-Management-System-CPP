#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "Global.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCureencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;


class clsCurrencyMainScreen : protected clsScreen
{

private:
	enum enCurrencyExchangeMenueOptions {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenue = 5
	};

	static short _ReadCurrencyExchangeMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static  void _GoBackToCurrencyExchangeMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";
		system("pause>0");
		ShowCurrencyExchangeMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrencyListScreen::ShowCurrenciesList();
		//cout << "\nCurrency List Screen Will Be Here.\n";
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCureencyScreen::ShowFindCurrencyScreen();
		//cout << "\nFind Currency Screen Will Be Here.\n";
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
		//cout << "\nUpdate Currency Rate Screen Will Be Here.\n";
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
		//cout << "\nCurrency Calculator Screen Will Be Here.\n";
	}

	static void _PerfromCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption)
	{
		switch (CurrencyExchangeMenueOption)
		{
		case enCurrencyExchangeMenueOptions::eListCurrencies:
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueOptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueOptions::eUpdateRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueOptions::eMainMenue:
		{
			//Do nothing to go back to main menue
		}
		}
	}

public:

	static void ShowCurrencyExchangeMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
		{
			return;// this will exit the function and it will not continue
		}

		system("cls");
		_DrawScreenHeader("\t Currency Exchange Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		short Choice = _ReadCurrencyExchangeMenueOption();
		_PerfromCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)Choice);
	}
};


