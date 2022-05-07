#include "std_lib_facilities.h"

struct Date {
    int y;a#include "std_lib_facilities.h"
struct Date {
    int y, m, d;                   
    Date(int y, int m, int d);      
    void add_day(int n);            
};

Date::Date(int yy, int mm, int dd)
    :y{ yy }, m{ mm }, d{ dd }
{
    if (m < 1 || 12 < m) error("Month is invalid!");
    if (d < 1 || 31 < d) error("Day is invalid!");
}

void Date::add_day(int n)
{
    d += n;
    if (d > 31) d %= 31;
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main()
try {
    Date today(1978, 6, 25);
    Date tomorrow = today;
    tomorrow.add_day(1);
    cout << today << '\n'
        << tomorrow << '\n';
    //Date bad_day(2004, 13, -5);
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "unknown error" << '\n';
    return 2;
}
    int m;
    int d;
};

void init_day(Date& dd, int y, int m, int d)
{
    if (m < 1 || m > 12) error("Month is invalid!");
    if (d < 1 || d > 31) error("Day is invalid!");

    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n)
{
    dd.d += n;
    if (dd.d > 31) dd.d %= 31;
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main()
{
    Date today;
    init_day(today, 1978, 6, 25);

    Date tomorrow = today;
    add_day(tomorrow, 1);
    cout << today << '\n'
         << tomorrow << '\n';
    //Date bad_day;
    //init_day(bad_day, 2004, 13, -5);
}