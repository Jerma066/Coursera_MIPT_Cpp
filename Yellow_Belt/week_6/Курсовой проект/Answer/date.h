#ifndef __DATE_H
#define __DATE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>

using namespace std;

class Date {
public:
    Date();
    Date(int y, int m, int d);
    ~Date();
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;


private:
    int year;
    int month;
    int day;
};

//Операторы ввода и вывода в/из поток для класса Date.
istream& operator>>(istream& stream, Date& date);
ostream& operator<< (ostream& stream, const Date& date);

//Реализация функции ParseDate
Date ParseDate(istream& stream);

//Проверки формата в ввода
void CheckDateFormat(const string& date);
void CheckValueFormat(const int& value, string type);

//Операторы сравнения
bool operator < (const Date& l_date, const Date& r_date);
bool operator == (const Date& , const Date& );
bool operator > (const Date& , const Date& );
bool operator >= (const Date& , const Date& );
bool operator <= (const Date& , const Date& );
bool operator !=(const Date& , const Date& );

#endif //__DATE_H
