#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

class clsBankClient : public clsPerson
{
private:

    enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string line, string seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(line, seperator);

        // return update mode
        return clsBankClient(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static vector<clsBankClient> _LoadDataClientFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLinetoClientObject(line);
                vClients.push_back(client);
            }

            MyFile.close();
            return vClients;
        }
    }

    static string _ConvertClientObjectToLine(clsBankClient client, string seperator = "#//#")
    {

        string ClientRecords;
        ClientRecords = client.FirstName + seperator;
        ClientRecords += client.LastName + seperator;
        ClientRecords += client.Email + seperator;
        ClientRecords += client.Phone + seperator;
        ClientRecords += client.AccountNumber() + seperator;
        ClientRecords += client.PinCode + seperator;
        ClientRecords += to_string(client._AccountBalance) + seperator;

        return ClientRecords;

    }

    void _RegisterTransferLog(float amount, clsBankClient destinationClient, string userName)
    {
        fstream Myfile;

        string line = _PrepareTransferLogLine(amount, destinationClient, userName);

		Myfile.open("TransferLog.txt", ios::out | ios::app);

        if (Myfile.is_open())
        {
			Myfile << line << endl;
            Myfile.close();
        }
    }

    static void _SaveClientDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            string line;

            for (clsBankClient& client : vClients)
            {
                if (client.MarkedForDeleted() == false)
                {
                    line = _ConvertClientObjectToLine(client);
                    MyFile << line << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> vClients;
        vClients = _LoadDataClientFromFile();

        for (clsBankClient& client : vClients)
        {
            if (client.AccountNumber() == AccountNumber())
            {
                client = *this;
                break;

            }
        }

        _SaveClientDataToFile(vClients);
    }

    void _AddDataLineToFile(string dataLine)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << dataLine << endl;
            MyFile.close();
        }
    }

    void _AddNewClient()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
    }

    struct stTransferLogRecord;

    static stTransferLogRecord _ConvertLineToTransferLogRecord(string line, string Seprator = "#//#")
    {
        vector<string> vLogData;
        vLogData = clsString::Split(line, Seprator);

        stTransferLogRecord LogRecord;
        LogRecord.dateTime = vLogData[0];
        LogRecord.sourceAccountNumber = vLogData[1];
        LogRecord.destinationAccountNumber = vLogData[2];
        LogRecord.amount = stof(vLogData[3]);
        LogRecord.srcBalanceAfter = stof(vLogData[4]);
        LogRecord.destBalanceAfter = stof(vLogData[5]);
		LogRecord.userName = vLogData[6];

        return LogRecord;
	}

    string _PrepareTransferLogLine(float amount, clsBankClient destinationClient ,string userName ,string Seprator = "#//#")
    {
        string clientRecord = "";
		clientRecord += clsDate::GetSystemDateTimeString() + Seprator;
        clientRecord += AccountNumber() + Seprator;
		clientRecord += destinationClient.AccountNumber() + Seprator;
		clientRecord += to_string(amount) + Seprator;
		clientRecord += to_string(_AccountBalance) + Seprator;
		clientRecord += to_string(destinationClient._AccountBalance) + Seprator;
		clientRecord += userName + Seprator;

        return clientRecord;
    }

public:

    struct stTransferLogRecord
    {
        string dateTime;
        string sourceAccountNumber;
        string destinationAccountNumber;
        float amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string userName;
    };

    clsBankClient(enMode mode, string firstName, string lastName, string phone, string email,
        string accountNumber, string pinCode, float accountBalance)
        : clsPerson(firstName, lastName, phone, email)
    {
        _Mode = mode;
        _PinCode = pinCode;
        _AccountBalance = accountBalance;
        _AccountNumber = accountNumber;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::emptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string pinCode)
    {
        _PinCode = pinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float accountBalance)
    {
        _AccountBalance = accountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    static clsBankClient Find(string accountNumber)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLinetoClientObject(line);
                if (client.AccountNumber() == accountNumber)
                {
                    MyFile.close();
                    return client;
                }
                vClients.push_back(client);
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();


    }

    static clsBankClient Find(string accountNumber, string pinCode)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLinetoClientObject(line);
                if (client.AccountNumber() == accountNumber && client.PinCode == pinCode)
                {
                    MyFile.close();
                    return client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();


    }

    static bool IsClientExist(string accountNumber)
    {
        clsBankClient client = clsBankClient::Find(accountNumber);

        return (!client.IsEmpty());
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save() {

        switch (_Mode)
        {
        case enMode::emptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }
        }
        case enMode::updateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;
        }

        case enMode::addNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNewClient();

                _Mode = enMode::updateMode;
                return enSaveResults::svSucceeded;
            }
        }

        return enSaveResults::svFaildEmptyObject;

        }
    }

    static clsBankClient GetAddNewClientObject(string accountNumber)
    {
        return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> vClients;
        vClients = _LoadDataClientFromFile();

        for (clsBankClient& client : vClients)
        {
            if (client.AccountNumber() == _AccountNumber)
            {
                client._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientDataToFile(vClients);

        *this = _GetEmptyClientObject();

        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadDataClientFromFile();
    }

    static float GetClientsBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        float totalBalances = 0;

        for (clsBankClient client : vClients)
        {
            totalBalances += client.AccountBalance;
        }

        return totalBalances;
    }


    void Deposit(float amount)
    {
        _AccountBalance += amount;
        Save();
    }

    bool Withdraw(float amount)
    {
        if (amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= amount;
            Save();
            return true;
        }
    }

    bool TransferTo(float amount, clsBankClient& toClient, string userName)
    {
        if (amount > _AccountBalance)
        {
            return false;
        }

		Withdraw(amount);
        toClient.Deposit(amount);
		_RegisterTransferLog(amount, toClient, userName);
		return true;
    }


    static vector <stTransferLogRecord> GetTransferLogScreen()
    {
        vector <stTransferLogRecord> vRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;

			struct stTransferLogRecord logRecord;

            while (getline(MyFile, line))
            {
				logRecord = _ConvertLineToTransferLogRecord(line);
				vRecord.push_back(logRecord);
            }

			MyFile.close();
        }

		return vRecord;
    }
};

