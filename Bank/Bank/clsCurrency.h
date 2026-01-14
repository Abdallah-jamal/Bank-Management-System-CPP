#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

    enum enMode { eEmtyCurrency = 0, eUpdateCurrency = 1 };

    enMode _Mode;

    string _Country;
    string _CurrencyName;
    string _CurrencyCode;
    float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(string line, string	seperator = "#//#")
    {
        vector <string> vCurrencyData;
        vCurrencyData = clsString::Split(line, seperator);

        // Trim fields to avoid leading/trailing spaces/newlines from file
        for (string &s : vCurrencyData)
        {
            s = clsString::Trim(s);
        }

        // File format (confirmed): Country#//#CurrencyName#//#CurrencyCode#//#Rate
        // Constructor expects: Country, CurrencyName, CurrencyCode, Rate
        if (vCurrencyData.size() >= 4)
        {
            return clsCurrency(enMode::eUpdateCurrency,
                vCurrencyData[0],
                vCurrencyData[1],
                vCurrencyData[2],
                static_cast<float>(stod(vCurrencyData[3])));
        }

        return _GetEmptyCurrencyObject();
    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string seperator = "#//#")
    {
        string sCurrencyRecord = "";

        sCurrencyRecord += Currency.Country() + seperator;
        sCurrencyRecord += Currency.CurrencyName() + seperator;
        sCurrencyRecord += Currency.CurrencyCode() + seperator;
        sCurrencyRecord += to_string(Currency.Rate());
        return sCurrencyRecord;
    }

    static vector <clsCurrency> _LoadCurrenciesFromFile()
    {
        fstream MyFile;

        vector <clsCurrency> vCurrencies;

        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;

            while (getline(MyFile, line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(line);
                if (!Currency.IsEmpty())
                {
                    vCurrencies.push_back(Currency);
                }
            }

            MyFile.close();
        }

        return vCurrencies;
    }


    static void _SaveCurrenciesToFile(vector <clsCurrency> vCurrencies)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);

        string dataLine = "";

        if (MyFile.is_open())
        {

            for (clsCurrency c : vCurrencies)
            {
                dataLine = _ConvertCurrencyObjectToLine(c);
                MyFile << dataLine << endl;
            }

            MyFile.close();
        }	
    }

    void _Update()
    {
        vector <clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

        for (clsCurrency& c : vCurrencies)
        {
            if (clsString::UpperAllString(clsString::Trim(c.CurrencyCode())) == clsString::UpperAllString(clsString::Trim(CurrencyCode())))
            {
                c = *this;
                break;
            }
        }

        _SaveCurrenciesToFile(vCurrencies);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::eEmtyCurrency, "", "", "", 0);
    }


public:

    clsCurrency()
    {

    }

    clsCurrency(enMode Mode, string Country, string CurrencyName, string CurrencyCode, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyName = CurrencyName;
        _CurrencyCode = CurrencyCode;
        _Rate = Rate;
    }

    bool IsEmpty() const
    {
        return _Mode == enMode::eEmtyCurrency;
    }

    string Country() const
    {
        return _Country;
    }

    string CurrencyName() const
    {
        return _CurrencyName;
    }

    string CurrencyCode() const
    {
        return _CurrencyCode;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    float Rate() const
    {
        return _Rate;
    }

    float ConvertTo(const clsCurrency &ToCurrency, float Amount) 
    {
        return Amount * (this->Rate() / ToCurrency.Rate());
    }

    static clsCurrency FindByCurrencyCode(string CurrencyCode)
    {
        fstream MyFile;

        // normalize input
        CurrencyCode = clsString::UpperAllString(clsString::Trim(CurrencyCode));

        MyFile.open("Currencies.txt", ios::in);
        
        if (MyFile.is_open())
        {
            string line;

            while (getline(MyFile, line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(line);

                // normalize the value read from file before comparing
                if (!Currency.IsEmpty() && clsString::UpperAllString(clsString::Trim(Currency.CurrencyCode())) == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        fstream MyFile;

        // normalize input
        Country = clsString::UpperAllString(clsString::Trim(Country));

        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;

            while (getline(MyFile, line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(line);

                if (!Currency.IsEmpty() && clsString::UpperAllString(clsString::Trim(Currency.Country())) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExistByCode(string CurrencyCode)
    {
        clsCurrency Currency = FindByCurrencyCode(CurrencyCode);
        return !Currency.IsEmpty();
    }

    static bool IsCurrencyExistByCountry(string Country)
    {
        clsCurrency Currency = FindByCountry(Country);
        return !Currency.IsEmpty();
    }

    static vector <clsCurrency> GetAllCurrencies()
    {
        return _LoadCurrenciesFromFile();
    }

};
