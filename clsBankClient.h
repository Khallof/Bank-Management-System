#pragma once
#include <iostream>
#include <string>
#include "D:\\OOP\clsPerson.h"
#include "D:\\OOP\clsString.h"
#include "D:\\OOP\Date.h"
#include "D:\\OOP\clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Separater = "#//#")
    {
        string TransferRecord = " ";
        TransferRecord += clsDate::GetSystemDateTimeString() + Separater;
        TransferRecord += AccountNumber() + Separater;
        TransferRecord += DestinationClient.AccountNumber() + Separater;
        TransferRecord += to_string(Amount) + Separater;
        TransferRecord += to_string(AccountBalance) + Separater;
        TransferRecord += to_string(DestinationClient.AccountBalance) + Separater;
        TransferRecord += UserName;
        return TransferRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinatioClient, string UserName)
    {
        string DataLine = _PrepareTransferLogRecord(Amount, DestinatioClient, UserName);
        fstream MyFile;
        MyFile.open("D:\\OOP\TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    struct stLoginTransferRecord;

    static stLoginTransferRecord _ConvertLoginTransferLineToRecord(string Line, string Separater = "#//#")
    {
        stLoginTransferRecord LoginTransferRecord;
        vector< string>vLoginTransferRecord = clsString::Split(Line, Separater);
        LoginTransferRecord.DateTime = vLoginTransferRecord[0];
        LoginTransferRecord.sAccountNumber = vLoginTransferRecord[1];
        LoginTransferRecord.dAccountNumber = vLoginTransferRecord[2];
        LoginTransferRecord.Amount = stof(vLoginTransferRecord[3]);
        LoginTransferRecord.sAccountBalance = stod(vLoginTransferRecord[4]);
        LoginTransferRecord.dAccoumtBalance = stod(vLoginTransferRecord[5]);
        LoginTransferRecord.UserName = vLoginTransferRecord[6];
        return LoginTransferRecord;
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("D:\\OOP\Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("D:\\OOP\Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("D:\\OOP\Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    struct stLoginTransferRecord
    {
        string DateTime;
        string sAccountNumber;
        string dAccountNumber;
        string UserName;
        float Amount;
        double sAccountBalance;
        double dAccoumtBalance;
    };


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("D:\\OOP\Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("D:\\OOP\Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientList()
    {
        return _LoadClientsDataFromFile();
    }

    static vector<stLoginTransferRecord>GetLoginTransferList()
    {
        vector<stLoginTransferRecord>vLoginTransferRecord;
        fstream MyFile;
        MyFile.open("D:\\OOP\TransferLog.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            stLoginTransferRecord LoginTransferRecord;
            while (getline(MyFile, Line))
            {
               LoginTransferRecord = _ConvertLoginTransferLineToRecord(Line);
               vLoginTransferRecord.push_back(LoginTransferRecord);
            }
            MyFile.close();
        }
        return vLoginTransferRecord;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool  Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool Transfer(float Amount,clsBankClient & DestinationClient,string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            Withdraw(Amount);

           DestinationClient.Deposit(Amount);

           _RegisterTransferLog(Amount, DestinationClient, UserName);

           return true;
        }
    }



    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }

};
