#pragma once
#include <iostream>
#include "D:\\OOP\clsScreen.h"
#include "D:\\OOP\clsCurrency.h"
#include <iomanip>

class clsCurrencyListScreen :protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(40) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.CurrencyCode();
		cout << "| " << setw(40) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();

	}

public:

	static void ShowCurrencyList()
	{
		vector<clsCurrency>vCurrency = clsCurrency::GetCurrenciesList();

		string Title = "\t  Currency List Screen";
		string SubTitle = "\t    (" + to_string(vCurrency.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(40) << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(10) << left << "Rate(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________________\n" << endl;
		if (vCurrency.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else
		for (clsCurrency C : vCurrency)
		{
			_PrintCurrencyRecordLine(C);
			cout << endl;
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________________\n" << endl;


	}
};

