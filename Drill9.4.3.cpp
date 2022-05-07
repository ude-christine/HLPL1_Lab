#include "std_lib_facilities.h"
class Date {
    int y;
    int m;
    int d;
public:
    Date(int y, int m, int d);      
    void add_day(int n);            
    int month() const { return m; }
    int day() const { return d; }
    int year() const { return y; }
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
    return os << '(' << d.year()
        << ',' << d.month()
        << ',' << d.day() << ')';
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
