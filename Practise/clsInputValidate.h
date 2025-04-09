#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <cctype>

class clsInputValidate
{

public:

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return Number >= From && Number <= To;
	}




	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From) && clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			return true;

		if (clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To) && clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			return true;

		return false;
	}



	static int ReadIntNumber(string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		double Number = 0;

		while (!(cin >> Number) || Number > (int)Number)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		double Number = 0;

		while (!(cin >> Number) || Number > (int)Number)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		double Number = 0.0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		float Number = 0.0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}





	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		short Number = ReadShortNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			Number = ReadShortNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static double ReadFloatNumberBetween(float From, float To, string ErrorMessage = "\nInvalid Number, Enter Again: ")
	{
		float Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << endl;
			Number = ReadDblNumber();
		}
		return Number;
	}

	
	
	
	
	
	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character 
		getline(cin >> ws, S1);
		return S1;
	}

	static bool ReadYesNo(const string& ErrorMessage = "Invalid Answer, [Y or N] ?")
	{
		char answer = ' ';
		cin >> answer;

		while (cin.fail() || (toupper(answer) != 'Y' && toupper(answer) != 'N'))
		{
			cin.clear();  // ÅÕáÇÍ ÍÇáÉ ÇáÎØÃ
			cin.ignore(1000, '\n');  // ÊÌÇåá ÇáÅÏÎÇá ÛíÑ ÇáÕÍíÍ
			cout << ErrorMessage;
			cin >> answer;
		}

		return (toupper(answer) == 'Y');
	}

};
