#pragma once
#include <iostream>
#include "iomanip"
#include "D:\\OOP\clsPerson.h"
#include "D:\\OOP\clsBankClient.h"
#include "D:\\OOP\clsScreen.h"

class clsLoginTransfer :protected clsScreen
{
private:

	static void _PrintLoginTransferRecordLine(clsBankClient::stLoginTransferRecord LoginTransferRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(23) << left << LoginTransferRecord.DateTime;
		cout << "|" << setw(9) << left << LoginTransferRecord.sAccountNumber;
		cout << "|" << setw(9) << left << LoginTransferRecord.dAccountNumber;
		cout << "|" << setw(9) << left << LoginTransferRecord.Amount;
		cout << "|" << setw(11) << left << LoginTransferRecord.sAccountBalance;
		cout << "|" << setw(11) << left << LoginTransferRecord.dAccoumtBalance;
		cout << "|" << setw(9) << left << LoginTransferRecord.UserName;
	}

public:

	static void ShowLoginTransferScreen()
	{
		vector<clsBankClient::stLoginTransferRecord >vLoginTransferRecord =
			clsBankClient::GetLoginTransferList();
		string Title = "\tLogin Transfer List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginTransferRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << setw(23) << left << "Date/Time";
		cout << "| " << setw(8) << left << "S.Acct";
		cout << "| " << setw(8) << left << "D.Acct";
		cout << "| " << setw(8) << left << "Amount";
		cout << "| " << setw(10) << left << "S.Balance";
		cout << "| " << setw(10) << left << "D.Balance";
		cout << "| " << setw(8) << left << "UserName";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________\n" << endl;
		if (vLoginTransferRecord.size() == 0)
			cout << "\t\t\t\tNo Logins Available In the System!";
		else
			for (clsBankClient::stLoginTransferRecord Logine : vLoginTransferRecord)
			{
				_PrintLoginTransferRecordLine(Logine);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________\n" << endl;


	}

};

