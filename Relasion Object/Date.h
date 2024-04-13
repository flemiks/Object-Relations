#pragma once
#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day=1, int month=1, int year=1990 ); 
    int getYear() const;
    void setYear(int year);
    int getMonth() const;
    void setMonth(int month);
    int getDay() const;
    void setDay(int day);

    static int getMaxDayInMonth(int month, int year);
    static bool isLeapYear(int year);
    static bool isValidDate(int day, int month, int year);

    friend Date operator+(const Date& date, int days);
    friend Date operator+(int daysToAdd, const Date& date);
    friend int operator-(const Date& date1, const Date& date2);
    friend Date operator-(const Date& date, int daysToCut);
    friend std::istream& operator>>(std::istream& input, Date& date);
    friend std::ostream& operator<<(std::ostream& output, const Date& date);

    Date& operator=(const Date& other);
    Date& operator++();       
    Date operator++(int);    
    Date& operator--();       
    Date operator--(int);     
    Date& operator+=(int days);
    Date& operator-=(int days);

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    std::string operator()(const std::string& format = "YYYY-MM-DD") const;
};
