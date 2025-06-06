#pragma once

#pragma warning (disable : 4996);

#include <iostream>
#include <string>
#include <ctime>
#include "clsString.h";

using namespace std;

class clsDate
{
private:
    short _Year = 1900;
    short _Month = 1;
    short _Day = 1;

public:

	clsDate()
	{
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
	}

    clsDate(string sDate)
    {
        vector<string> vDate;

        vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        _Year = Year;
        clsDate Date = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Year = Date.Year;
        _Month = Date.Month;
        _Day = Date.Day;
    }

    void SetYear(short Year)
    {
        _Year = Year;
    }
    
    short GetYear()
    {
        return _Year;
    }

    void SetMonth(short Month)
    {
        _Month = Month;
    }

    short GetMonth()
    {
        return _Month;
    }

    void SetDay(short Day)
    {
        _Day = Day;
    }

    short GetDay()
    {
        return _Day;
    }

    __declspec(property(get = GetYear, put = SetYear))short Year;
    __declspec(property(get = GetMonth, put = SetMonth))short Month;
    __declspec(property(get = GetDay, put = SetDay))short Day;

    static bool IsLeapYear(short Year)
    {
        return(Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }
    
    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;

        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        // Gregorian:
        // 0:sun, 1:Mon, 2:Tue...etc

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thrusday","Friday","Saturday" };
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayName(short Day, short Month, short Year)
    {
        string arrDayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thrusday","Friday","Saturday" };
        return arrDayNames[(Day, Month, Year)];
    }

    string DayName()
    {
        string arrDayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thrusday","Friday","Saturday" };
        return arrDayNames[(_Day, _Month, _Year)];
    }

    static string MonthShortName(short Month)
    {
        string arrMonthNames[] = { "","Jan", "Feb", "Mar","Apr", "May", "Jun", "Jul","Aug","Sep","Oct","Nov","Dec" };
        return arrMonthNames[Month];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalender(short Month, short Year)
    {
        // index of the day from 0 to 6
        short Current = DayOfWeekOrder(1, Month, Year);

        short NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        // print the current month name
        printf("\n _______________%s_______________\n\n",
            MonthShortName(Month).c_str());

        // print thr columns
        printf("  Sun  Mon  Tue  Wed  Thr  Fri  Sat\n");

        // print appropriate spaces
        short i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (short j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n _________________________________\n");
    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(_Month, _Year);
    }

    static void PrintYearCalender(short Year)
    {
        printf("\n _________________________________\n\n");
        printf("          Calender - %d\n", Year);
        printf(" _________________________________\n");

        for (short i = 1; i <= 12; i++)
        {
            PrintMonthCalender(i, Year);
        }
    }

    void PrintYearCalendar()
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", _Year);
        printf("  _________________________________\n");


        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalender(i, _Year);
        }

        return;
    }

    static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;

        for (short i = 0; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }

        TotalDays += Day;
        return TotalDays;
    }

    short NumberOfDaysFromTheBeginingOfTheYear()
    {

        short TotalDays = 0;

        for (int i = 1; i <= _Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, _Year);
        }

        TotalDays += _Day;

        return TotalDays;
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }
        return Date;
    }

    void AddDays(short Days, clsDate Date)
    {
        short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;

        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true :
            ((Date1.Year == Date2.Year) ?
                (Date1.Month < Date2.Month ? true :
                    (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        //note: *this sends the current object :-)
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return
            (Date1.Year == Date2.Year) ?
            ((Date1.Month == Date2.Month) ?
                ((Date1.Day == Date2.Day) ? true : false) :
                false) :
            false;
    }

    bool IsDate1EqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date.Month))
            {
                Date.Month = 1;
                Date.Day = 1;
                Date.Year++;
            }
            else
            {
                Date.Month++;
                Date.Day = 1;
            }
        }
        else
        {
            Date.Day++;
        }

        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    static clsDate GetSystemDate()
    {
        clsDate Date;

        time_t t = time(0);
        tm* Now = localtime(&t);

        short Year, Month, Day,Hour,Minute,Second;

        Year = Now->tm_year + 1900;
        Month = Now->tm_mon + 1;
        Day = Now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    static string GetSystemDateTimeString()
    {
        clsDate Date;

        time_t t = time(0);
        tm* Now = localtime(&t);

        short Year, Month, Day, Hour, Minute, Second;

        Year = Now->tm_year + 1900;
        Month = Now->tm_mon + 1;
        Day = Now->tm_mday;
        Hour = Now->tm_hour;
        Minute = Now->tm_min;
        Second = Now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/" +
            to_string(Year) + " - " +
            to_string(Hour) + ":" + to_string(Minute) + ":" +
            to_string(Second));
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }
        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);

    }

    static clsDate IncreaseDateByXDay(short Days, clsDate& Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDay(short Days)
    {
        IncreaseDateByXDay(Days, *this);
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate IncreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        /* Last check day in date should not exceed max days in the current month
         example if date is 31/1/2024 increasing one month
         should not be 31/2/2024, it should be 28/2/2024 */

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }
    
    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        if (IsLeapYear(Date.Year) && Date.Month == 2 && Date.Day == 29)
        {
            Date.Year++;
            Date.Month = 2;
            Date.Day = 28;
            return Date;
        }
        else
        {
            Date.Year++;
            return Date;
        }
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
    {
        for (short i = 1; i <= Years; i++)
        {
            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    static clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(short Decade, clsDate& Date)
    {
        Date.Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        IncreaseDateByXDecades(Decade, *this);
    }

    static clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate Date)
    {
        Date.Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    static clsDate DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Year--;
                Date.Month = 12;
                Date.Day = 31;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        DecreaseDateByOneDay(*this);
    }
    
    static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    
    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    
    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }
    
    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        /* Last check day in date should not exceed max days in the current month
         example if date is 31/1/2024 increasing one month
         should not be 31/2/2024, it should be 28/2/2024 */

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }
    
    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }
  
    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        if (IsLeapYear(Date.Year) && Date.Month == 2 && Date.Day == 29)
        {
            Date.Year--;
            Date.Month = 2;
            Date.Day = 28;
            return Date;
        }
        else
        {
            Date.Year--;
            return Date;
        }
    }
  
    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year -= 10;
        return Date;
    }
    
    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }
    
    static clsDate DecreaseDateByXDecades(short Decade, clsDate& Date)
    {
        Date.Year -= Decade * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year -= 100;
        return Date;
    }
    
    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
    }

    bool IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        //Weekends are Fri and Sat
        short WeekEnd = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        return WeekEnd == 5 || WeekEnd == 6;
    }

    bool IsWeekEnd()
    {
        return  IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        //Weekends are Sun,Mon,Tue,Wed and Thur

        /*short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex >= 0 && DayIndex <= 4);*/

        //shorter method is to invert the IsWeekEnd: this will save updating code.
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return  IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

    short DaysUntilTheEndOfWeek()
    {
        return  DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date)
    {
        clsDate EndOfMonthDate;
        EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        EndOfMonthDate.Month = Date.Month;
        EndOfMonthDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date)
    {
        clsDate EndOfYearDate;
        EndOfYearDate.Month = 12;
        EndOfYearDate.Day = 31;
        EndOfYearDate.Year = Date.Year;

        return GetDifferenceInDays(Date, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return  DaysUntilTheEndOfYear(*this);
    }

    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short DaysCount = 0;

        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                DaysCount++;

            DateFrom = AddOneDay(DateFrom);
        }
        return DaysCount;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        /*short Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = AddOneDay(DateFrom);
        }*/

        return CalculateBusinessDays(DateFrom, DateTo);

    }
    //above method is eough , no need to have method for the object

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;

        for (short i = 1; i <= VacationDays; i++)
        {

            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = AddOneDay(DateFrom);
        }
        //to add weekends 
        for (short i = 1; i <= WeekEndCounter; i++)
            DateFrom = AddOneDay(DateFrom);

        return DateFrom;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enCompareDates { Before = -1, Equal = 0, After = 1 };

    static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
    {
        enCompareDates CompareDates;

        if (IsDate1BeforeDate2(Date1, Date2))
            return enCompareDates::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enCompareDates::Equal;

        //if (IsDate1AfterDate2(Date1, Date2))
        //    return enCompareDates::After;

        // Faster
        else
            return enCompareDates::After;

    }

    enCompareDates CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

    static bool IsValidDate(clsDate Date)
    {
        if (Date.Month < 1 || Date.Month > 12)
            return false;

        if (Date.Day < 1 || Date.Day > 31)
            return false;

        if (Date.Month == 2)
        {
            if (IsLeapYear(Date.Year))
            {
                if (Date.Day > 29)
                    return false;
            }
        }
        else
        {
            if (Date.Day > 28)
                return false;
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > DaysInMonth)
            return false;

        return true;

        // Optimize 
        // return Date.Day > 0 && Date.Day <= (NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }
    
    string DateToString()
    {
        return DateToString(*this);
    }

    void Print()
    {
        cout << DateToString() << endl;
    }
   
};

