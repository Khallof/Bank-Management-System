#pragma once
#include <iostream>
#include "D:\\OOP\clsScreen.h"
#include "D:\\OOP\clsInputValidate.h"
#include "D:\\OOP\clsCurrency.h"

class clsUpdateCurrencyRate:protected clsScreen
{
private:
	static float _ReadNewRate()
	{
		float NewRate;
		cout << "\nEnter New Rate?";
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n\t Client Card";
		cout << "\n___________________________________";
		cout << "\nCountry  :" << Currency.Country();
		cout << "\nCode     :" << Currency.CurrencyCode();
		cout << "\nName     :" << Currency.CurrencyName();
		cout << "\nRate(1$) =" << Currency.Rate();
		cout << "\n___________________________________";
	}

public:
	static void ShowUpdateCurrencyRate()
	{
		_DrawScreenHeader("\nUpdate Currency Rate");
		cout << "Please Enter CurrencyCode? ";
		string CurrencyCode;
		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCountry Was Not Found , Pleas Enter Another CurrencyCode? ";

			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);
		cout << "\nAre You Sure Do You Want To Update The Rate Of The Currency? Y/N? ";
		char Answer = 'n';
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate Currency Rate\n";

			cout << "___________________________\n\n";

			Currency.UpdateRate(_ReadNewRate());

			cout << "\nCurrency Rate Updated Successfully :-)";

			_PrintCurrencyCard(Currency);
			
		}
		
	}

};

