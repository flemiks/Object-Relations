#include "Date.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <array>

using namespace std;

constexpr int MONTHS_IN_YEAR = 12;
constexpr array<int, MONTHS_IN_YEAR> DAYS_IN_MONTH = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(int day, int month, int year) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

int Date::getYear() const {
    return year;
}

void Date::setYear(int year) {
    if (year < 0) {
        throw invalid_argument("Year cannot be less than 0");
    }
    this->year = year;
}

int Date::getMonth() const {
    return month;
}

void Date::setMonth(int month) {
    if (month < 1 || month > 12) {
        throw invalid_argument("Month must be between 1 and 12");
    }
    this->month = month;
}

int Date::getDay() const {
    return day;
}

void Date::setDay(int day) {
    if (day < 1 || day > getMaxDayInMonth(month, year)) {
        throw invalid_argument("Invalid day for given month and year");
    }
    this->day = day;
}

int Date::getMaxDayInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    return DAYS_IN_MONTH[month - 1];
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || year < 0) return false;
    return day >= 1 && day <= getMaxDayInMonth(month, year);
}

Date operator+(const Date& date, int daysToAdd) {
    Date result = date;
    result.day += daysToAdd;
    while (result.day > Date::getMaxDayInMonth(result.month, result.year)) {
        result.day -= Date::getMaxDayInMonth(result.month, result.year);
        result.month++;
        if (result.month > 12) {
            result.month = 1;
            result.year++;
        }
    }
    return result;
}

Date operator+(int daysToAdd, const Date& date) {
    return date + daysToAdd;
}

int operator-(const Date& date1, const Date& date2) {
    int n1 = date1.year * 365 + date1.day;
    for (int i = 0; i < date1.month - 1; i++) {
        n1 += DAYS_IN_MONTH[i];
    }

    int n2 = date2.year * 365 + date2.day;
    for (int i = 0; i < date2.month - 1; i++) {
        n2 += DAYS_IN_MONTH[i];
    }

    return n1 - n2;
}

Date operator-(const Date& date, int daysToCut) {
    Date result = date;
    result.day -= daysToCut;
    while (result.day <= 0) {
        result.month--;
        if (result.month < 1) {
            result.month = 12;
            result.year--;
        }
        result.day += Date::getMaxDayInMonth(result.month, result.year);
    }
    return result;
}

istream& operator>>(istream& input, Date& date) {
    int day, month, year;
    char delim1, delim2;
    if (input >> day >> delim1 >> month >> delim2 >> year) {
        if (delim1 == '-' && delim2 == '-' && Date::isValidDate(day, month, year)) {
            date = Date(day, month, year);
        }
        else {
            input.setstate(ios_base::failbit);
        }
    }
    return input;
}

ostream& operator<<(ostream& output, const Date& date) {
    output << setw(4) << setfill('0') << date.year << '-'
        << setw(2) << date.month << '-'
        << setw(2) << date.day;
    return output;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }
    return *this;
}

Date& Date::operator++() {
    *this = *this + 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    *this = *this - 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    --(*this);
    return temp;
}

Date& Date::operator+=(int days) {
    *this = *this + days;
    return *this;
}

Date& Date::operator-=(int days) {
    *this = *this - days;
    return *this;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator>(const Date& other) const {
    return !(*this < other) && !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

string Date::operator()(const string& format) const {
    ostringstream formattedDate;
    for (char c : format) {
        switch (c) {
        case 'Y': formattedDate << setw(4) << setfill('0') << year; break;
        case 'M': formattedDate << setw(2) << setfill('0') << month; break;
        case 'D': formattedDate << setw(2) << setfill('0') << day; break;
        default: formattedDate << c; break;
        }
    }
    return formattedDate.str();
}
