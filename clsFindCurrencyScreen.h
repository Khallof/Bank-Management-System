#pragma once
#include <iostream>
#include "D:\\OOP\clsScreen.h"
#include "D:\\OOP\clsInputValidate.h"
#include "D:\\OOP\clsCurrency.h"

class clsFindCurrencyScreen:protected clsScreen
{

private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n\tCourrency Card:\n";
		cout << "\n_________________________________";
		cout << "\nCountry  :" << Currency.Country();
		cout << "\nCode     :" << Currency.CurrencyCode();
		cout << "\n Name    :" << Currency.CurrencyName();
		cout << "\nRate(1$) =" << Currency.Rate();
		cout << "\n_________________________________";
	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "Country Found :-)";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "Country Was Not Foundn :-(";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\nFind Currency Screen!");
		cout << "\nFind By : [1] Code Or [2] Country ?";
		short Answer = 1;
		cin >> Answer;
		if (Answer == 1)
		{
			string CurrencyCode;
			cout << "\nPlease Enter CurrencyCode? ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency);
		}
		else
		{
			string Country;
			cout << "\nPlease Enter Country Name? ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
	}
};

