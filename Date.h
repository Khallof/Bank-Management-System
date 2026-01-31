#pragma once
#include<iostream>
using namespace std;

namespace Date
{
    enum enCompareDates { DateBefor = -1, DateEqual = 0, DateAfter = 1 };

    struct sDate
    {
        short Year;
        short Month;
        short Day;
    };

    struct stPeriod
    {
        sDate StartDate;
        sDate EndDate;
    };

    short ReadDay()
    {
        short Day;
        cout << "\nPlease enter a Day? ";
        cin >> Day;
        return Day;
    }

    short ReadMonth()
    {
        short Month;
        cout << "Please enter a Month? ";
        cin >> Month;
        return Month;
    }

    short ReadYear()
    {
        short Year;
        cout << "Please enter a Year? ";
        cin >> Year;
        return Year;
    }

    sDate ReadFullDate()
    {
        sDate Date;
        Date.Day = ReadDay();
        Date.Month = ReadMonth();
        Date.Year = ReadYear();
        return Date;
    }

    stPeriod ReadPeriod()
    {
        stPeriod Period;
        cout << "\nRead Start Date:\n";
        Period.StartDate = ReadFullDate();
        cout << "\nRead End Date";
        Period.EndDate =ReadFullDate();
        return Period;
    }

    bool isLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
            Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
                Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    bool IsDate1EqualDate2(sDate Date1, sDate Date2)
    {
        return (Date1.Year == Date2.Year) ? ((Date1.Month ==
            Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false): false;
    }


    bool IsDate1AfterDate2(sDate Date1, sDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }


    short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month>12)
            return 0;
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) :
            days[Month - 1];
    }

    bool IsLastDayInMonth(sDate Date)
    {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month,   Date.Year));
    }

    bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    sDate IncreaseDateByOneDay(sDate Date)
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
                Date.Day = 1;
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }
        return Date;
    }

    short GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDate = false)
    {
        int Day = 0;
        if (IsDate1BeforeDate2(Date1, Date2))
        {
            Day++;
            Date1 = IncreaseDateByOneDay(Date1);
        }
        return IncludeEndDate ? ++Day : Day;
    }

    short DateofweekOrder(short Day, short Month, short Year)
    {
        int y, m, a;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DateofweekOrder(sDate Date)
    {
        return DateofweekOrder(Date.Day, Date.Month, Date.Year);

    }


    string DayShortName(short DateofweekOrder)
    {
        string arrString[7] = { "Sun","Mon","Tue","Wen","Thu","Fri","Sat" };
        return arrString[DateofweekOrder];
    }

    short IsEndOfWeek(sDate Date)
    {
        return DateofweekOrder(Date) == 6;
    }

    bool IsWeekEnd(sDate Date)
    {
        //Weekends are Fri and Sat
        short DayIndex = DateofweekOrder(Date);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsBusinessDay(sDate Date)
    {
        //Weekends are Sun,Mon,Tue,Wed and Thur
        /* short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex >= 5 && DayIndex <= 4);
        */
        //shorter method is to invert the IsWeekEnd: this will save	updating code.
        return !IsWeekEnd(Date);
    }


    short CalculatVocationDays(sDate Date1, sDate Date2)
    {
        short Day = 0;
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            if (IsBusinessDay(Date1))
                Day++;

            Date1 = IncreaseDateByOneDay(Date1);
        }
        return Day;
    }

    enCompareDates CompareDates(sDate Date1, sDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enCompareDates::DateBefor;
        if (IsDate1EqualDate2(Date1, Date2))
            return enCompareDates::DateEqual;



        return enCompareDates::DateAfter;
    }


    int PeriodLengthInDays(stPeriod Period, bool IncludeEndDate = false)
    {
        return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
    }
    

    bool isOverLapPeriod(stPeriod Perio1, stPeriod Period2)
    {
        if (CompareDates(Period2.EndDate,Perio1.StartDate) == enCompareDates::DateBefor
            || CompareDates(Period2.StartDate,Perio1.EndDate) == enCompareDates::DateAfter)
            return false;
        else
            return true;

       

    }
    bool isDateInPeriod(sDate Date, stPeriod Period)
    {
        return !(CompareDates(Date, Period.StartDate) ==
            enCompareDates::DateBefor || CompareDates(Date, Period.EndDate) ==
            enCompareDates::DateAfter);
    }


    int CountOverLapDays(Date::stPeriod Period1, Date::stPeriod Period2)
    {
        short Period1Length = Date::PeriodLengthInDays(Period1);
        short Period2Length = Date::PeriodLengthInDays(Period2);
        short OverLapDays = 0;
        if (!Date::isOverLapPeriod(Period1, Period2))
            return 0;
        if (Period1Length < Period2Length)
        {
            while (Date::IsDate1BeforeDate2(Period1.StartDate, Period2.EndDate))
            {
                if (Date::isDateInPeriod(Period1.StartDate, Period2))
                    OverLapDays++;

                Period1.StartDate = Date::IncreaseDateByOneDay(Period1.StartDate);
            }
        }
        else
        {
            while (Date::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
            {
                if (Date::isDateInPeriod(Period2.StartDate, Period1))
                    OverLapDays++;
                Period2.StartDate = Date::IncreaseDateByOneDay(Period2.StartDate);
            }
        }
        return OverLapDays;
    }

    bool IsValidDate(Date::sDate Date)
    {
        if (Date.Day < 1 || Date.Day>31)
            return false;
        if (Date.Month < 1 || Date.Month>12)
            return false;
        if (Date.Month == 2)
        {
            if (Date::isLeapYear(Date.Year))
            {
                if (Date.Day > 29)
                    return false;
            }
            else
            {
                if (Date.Day > 28)
                    return false;
            }
        }
        short NumberDays = Date::NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > NumberDays)
            return false;

        return true;

    }
    vector<string>SplitString(string S1, string Delim)
    {
        vector<string>Vstring;
        string Sword;
        short Pos = 0;
        while ((Pos = S1.find(Delim)) != std::string::npos)
        {
            Sword = S1.substr(0, Pos);
            if (Sword != " ")
            {
                Vstring.push_back(Sword);
            }
            S1.erase(0, Pos + Delim.length());
        }
        if (S1 != " ")
        {
            Vstring.push_back(S1);
        }
        return Vstring;

    }
    string DateToString(sDate Date1)
    {
        return to_string(Date1.Day) + "/" + to_string(Date1.Month) + "/" + to_string(Date1.Year);
    }
    sDate StringToDate(string DateString)
    {
        Date::sDate Date1;
        vector<string>vDate1;
        vDate1 = SplitString(DateString, "/");
        Date1.Day = stoi(vDate1[0]);
        Date1.Month = stoi(vDate1[1]);
        Date1.Year = stoi(vDate1[2]);
        return Date1;
    }
    string ReadStringDate(string Message)
    {
        string DateString;
        cout << Message;
        getline(cin >> ws, DateString);
        return DateString;
    }
    string ReplaceWordInString(string S1, string sWordToReplace, string sReplaceTo)
    {
        short Pos = S1.find(sWordToReplace);
        while (Pos != std::string::npos)
        {
            S1 = S1.replace(Pos, sWordToReplace.length(), sReplaceTo);
            Pos = S1.find(sWordToReplace);
        }
        return S1;
    }
    string FormateDate(sDate Date, string DateFormat = "dd/mm/yyyy")
    {
        string DateFormateString = " ";
        DateFormateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
        DateFormateString = ReplaceWordInString(DateFormateString, "mm", to_string(Date.Month));
        DateFormateString = ReplaceWordInString(DateFormateString, "yyyy", to_string(Date.Year));
        return DateFormateString;
    }

}
