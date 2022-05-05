//_____________________________DRILL6 (9.4.1)______________________________________
/*
   This drill simply involves getting the sequence of versions of Date to work.
   For each version define a Date called today initialized to June 25, 1978.
   Then, define a Date called tomorrow and give it a value by copying today into it
   and increasing its  day  by  one  using  add_day().
   Finally,  output  today  and tomorrow using  a  <<  defined as in §9.8.
   Your check for a valid date may be very simple.
   Feel free to ignore leap years.
   However, don’t accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
   Test each version with at least one invalid date (e.g., 2004, 13, –5).
   1.  The version from §9.4.1
 */

#include "std_lib_facilities.h"

using namespace std;

struct Date {
        int year;
        int month;
        int day;

};


void init_day(Date& dd, int year, int month, int day)
{

        if(month < 1 || month > 12 )
                error("Invalid month");
        if(day <1 || day > 31)
                error("Invalid day");


        dd.year=year;
        dd.month=month;
        dd.day=day;
}

void add_day(Date& dd, int x)
{
        dd.day +=x;

        if(dd.day>31)
        {
                dd.day=1;
                ++dd.month;
        }
        if(dd.month>12)
        {
                dd.month=1;
                ++dd.year;
        }
}

ostream& operator<<(ostream& os, Date& d)
{
        return os << d.year << "-" << d.month << "-" << d.day << endl;
}

void f()
{
        try{
                Date today;
                init_day(today, 1978,6,25);
                //Date baddate;
                //init_day(baddate, 2004.13,-5)

                Date tomorrow = today;
                add_day(tomorrow, 1);

                cout << "Today's date: " << today << endl;
                cout << "Tomorrow's date: " << tomorrow << endl;
        }
        catch(exception& e)
        {
                cerr << e.what() << endl;
        }
}

int main()
{
        f();

        return 0;
}
