#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h";

using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode, UpdateMode };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator)
	{
		vector<string> vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(UpdateMode, vCurrencyData.at(0), vCurrencyData.at(1), vCurrencyData.at(2), stof(vCurrencyData.at(3)));
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile(string FileName, string Separator)
	{
		vector<clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open(FileName, ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line, Separator);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator)
	{
		string CurrencyRecord = "";

		CurrencyRecord += Currency._Country + Separator;
		CurrencyRecord += Currency._CurrencyCode + Separator;
		CurrencyRecord += Currency._CurrencyName + Separator;
		CurrencyRecord += to_string(Currency._Rate);

		return CurrencyRecord;
	}

	static void _SaveCurrenciesDataToFile(string FileName, vector<clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out);
		if (MyFile.is_open())
		{
			for (const clsCurrency& Currency : vCurrencies)
				MyFile << _ConvertCurrencyObjectToLine(Currency, Separator) << endl;


			MyFile.close();
		}

	}

	void _Update()
	{
		if (_Mode == EmptyMode)
			return;

		vector<clsCurrency> _vCurrencies = _LoadCurrenciesDataFromFile(CurrenciesFileName, Separator);

		for (clsCurrency& Currency : _vCurrencies)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				/*Currency = *this;
				break;*/
				Currency._Rate = this->_Rate;
			}
		}
		_SaveCurrenciesDataToFile(CurrenciesFileName, _vCurrencies);
	}

	static clsCurrency GetEmptyCurrencyObject()
	{
		return clsCurrency(EmptyMode, "", "", "", 0.0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static const string CurrenciesFileName, Separator;

	string Country()const
	{
		return _Country;
	}

	string CurrencyCode()const
	{
		return _CurrencyCode;
	}

	string CurrencyName()const
	{
		return _CurrencyName;
	}

	float Rate()const
	{
		return _Rate;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open(CurrenciesFileName, ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line, Separator);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open(CurrenciesFileName, ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line, Separator);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return !Currency.IsEmpty();
	}

	static vector<clsCurrency> GetCurrencyList()
	{
		return _LoadCurrenciesDataFromFile(CurrenciesFileName, Separator);
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());
	}

};

const string clsCurrency::CurrenciesFileName = "Currencies.txt";
const string clsCurrency::Separator = "#//#";