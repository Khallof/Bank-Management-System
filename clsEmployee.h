#pragma once
#include <iostream>
#include "D:\\OOP\clsPerson.h"
using namespace std;
class clsEmployee :public clsPerson
{
private:
	string _Titel;
	string _Department;
	float _Salary;
public:
	clsEmployee(int ID, string FirstName, string LastName, string Email, string PhoneNumber, string Titel, string Department, float Salary)
		:clsPerson(ID, FirstName, LastName, Email, PhoneNumber)
	{
		_Titel = Titel;
		_Department = Department;
		_Salary = Salary;
	}
	void SetSalary(float Salary)
	{
		_Salary = Salary;
	}
	float Salary()
	{
		return _Salary;
	}
	void SetTitel(string Titel)
	{
		_Titel = Titel;
	}
	string Titel()
	{
		return _Titel;
	}
	void SetDepartment(string Department)
	{
		_Department = Department;
	}
	string Department()
	{
		return _Department;
	}
	void Print()
	{
		cout << "\nInfo:";
		cout << "\n\n______________________________\n\n";
		cout << "ID        :" << ID() << endl;
		cout << "First Name:" << FirstName() << endl;
		cout << "Last Name :" << LastName() << endl;
		cout << "Full Name :" << FullName() << endl;
		cout << "Email     :" << Email() << endl;
		cout << "Phone     :" << PhoneNumber() << endl;
		cout << "Titel     :" << _Titel << endl;
		cout << "Department:" << _Department << endl;
		cout << "Salary    :" << _Salary;
		cout << "\n______________________________\n";

	}
};