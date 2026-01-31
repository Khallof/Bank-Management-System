#pragma once
#include <iostream>
#include <iomanip>
#include "D:\\OOP\clsScreen.h"
#include "D:\\OOP\clsInputValidate.h"
#include "D:\\OOP\clsUser.h"
#include "D:\\OOP\clsCurrencyListScreen.h"
#include "D:\\OOP\clsFindCurrencyScreen.h"
#include "D:\\OOP\clsUpdateCurrencyRate.h"
#include "D:\\OOP\clsCurrencyCalculaterScreen.h"

class clsCurrencyExchangeMainScreen :protected clsScreen
{
private:
	enum enCurrencyScreen {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculater = 4, eMainMenueShow = 5
	};

	static short _ReadCurrencyMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static  void _GoBackToCurrencyMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Menue...\n";

		system("pause>0");
		ShowCurrencyMenue();
	}

	static void _ShowListCurrenciesScreen()
	{
		//cout << "\nList Currency Will Be Here.";
		clsCurrencyListScreen::ShowCurrencyList();
	}
	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will Be Here.";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		//cout << "\nUpdate Rate Screen Will Be Here.";
		clsUpdateCurrencyRate::ShowUpdateCurrencyRate();
	}
	static void _ShowCurrencyCalculaterScreen()
	{
		//cout << "\nCurrency Calculater Screen Will Be Here.";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PeerfromCurrencyMainScreenOption(enCurrencyScreen CurrencyScreen)
	{
		switch (CurrencyScreen)
		{
		case enCurrencyScreen::eListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case enCurrencyScreen::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case enCurrencyScreen::eUpdateRate:
		{
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case enCurrencyScreen::eCurrencyCalculater:
		{
			system("cls");
			_ShowCurrencyCalculaterScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case enCurrencyScreen::eMainMenueShow:
		{

		}
		}
	}




public:

	static void ShowCurrencyMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pShowCurrency))
		{
			return;// this will exit the function and it will not continue
		}


		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "[1] List Currencies.\n";
		cout << setw(37) << left << "" << "[2] Find Currency.\n";
		cout << setw(37) << left << "" << "[3] Update Rate.\n";
		cout << setw(37) << left << "" << "[4] Currency Calculater.\n";
		cout << setw(37) << left << "" << "[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PeerfromCurrencyMainScreenOption((enCurrencyScreen)_ReadCurrencyMenueOption());
	}

	

};

