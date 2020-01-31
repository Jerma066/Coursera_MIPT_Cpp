#include "date.h"

Date::Date()
    :year(0),
    month(0),
    day(0){
}

Date::Date(int y, int m, int d)
    :year(y),
    month(m),
    day(d){
}

Date::~Date(){
}

int Date::GetYear() const{
    return year;
}
int Date::GetMonth() const{
    return month;
}
int Date::GetDay() const{
    return day;
}

void CheckDateFormat(const string& date){
    stringstream input(date);
    int number;
    char bufSym;

    input >> number;

    if(input.peek() == '-'){input.ignore(1);}
    else{throw invalid_argument("Wrong date format: " + date);}

    //Переход к полю, которое фактически должно быть месяцем
    bufSym = input.peek();
    if((bufSym == '-') || (bufSym == '+')){
        input >> bufSym;
    }

    bufSym = input.peek();
    if((bufSym >= '0' && bufSym <= '9')){
        input >> number;
    }
    else{throw invalid_argument("Wrong date format: " + date);}

    if(input.peek() == '-'){input.ignore(1);}
    else{throw invalid_argument("Wrong date format: " + date);}

    //Переход к полю, которое фактически должно быть днем
    bufSym = input.peek();
    if((bufSym == '-') || (bufSym == '+')){
        input >> bufSym;
    }

    bufSym = input.peek();
    if((bufSym >= '0' && bufSym <= '9')){
        input >> number;
    }
    else{throw invalid_argument("Wrong date format: " + date);}

    if(input.peek() != -1){
        throw invalid_argument("Wrong date format: " + date);
    }
}

void CheckValueFormat(const int& value, string type){
    stringstream ss;
    ss << value;
    if(type == "Month"){
        if( value < 1 || value > 12){
            throw invalid_argument(type +" value is invalid: " + ss.str());
        }
    }
    if(type == "Day"){
        if( value < 1 || value > 31){
            throw invalid_argument(type +" value is invalid: " + ss.str());
        }
    }

}

//Оператор сравнение < для работы с контейнером map
bool operator < (const Date& l_date, const Date& r_date){
    if(l_date.GetYear() == r_date.GetYear()){
        if(l_date.GetMonth() == r_date.GetMonth()){
            return l_date.GetDay() < r_date.GetDay();
        }
        else{
            return l_date.GetMonth() < r_date.GetMonth();
        }
    }
    else{
        return l_date.GetYear() < r_date.GetYear();
    }
}

//Все остальные операторы сравнения
bool operator == (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() == rhs.GetDay();
        }
    }
    return false;
}
bool operator > (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() > rhs.GetDay();
        } else {
            return lhs.GetMonth() > rhs.GetMonth();
        }
    }
    return lhs.GetYear() > rhs.GetYear();
}
bool operator >= (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() >= rhs.GetDay();
        } else {
            return lhs.GetMonth() >= rhs.GetMonth();
        }
    }
    return lhs.GetYear() >= rhs.GetYear();
}
bool operator <= (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() <= rhs.GetDay();
        } else {
            return lhs.GetMonth() <= rhs.GetMonth();
        }
    }
    return lhs.GetYear() <= rhs.GetYear();
}

bool operator != (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() != rhs.GetDay();
        }
    }
    return true;
}

ostream& operator << (ostream& stream, const Date& date){
    stream << setfill('0');

    int buffer;
    if(date.GetYear() < 0){
        buffer = abs(date.GetDay());
        stream << '-' << setw(4) << buffer <<'-';
    }
    else{
        stream << setw(4) << date.GetYear() <<'-';
    }

    stream << setw(2) << date.GetMonth()<<'-'
           << setw(2) << date.GetDay();

    return stream;
}

istream& operator >> (istream& stream, Date& date){
    string buffer;
    getline(stream, buffer);
    stringstream input(buffer);

    CheckDateFormat(buffer);

    int value_y, value_m, value_d;
    if(stream){
        input >> value_y;
        input.ignore(1);
        input >> value_m;
        CheckValueFormat(value_m, "Month");
        input.ignore(1);
        input >> value_d;
        CheckValueFormat(value_d, "Day");
    }

    Date date1(value_y, value_m, value_d);
    date = date1;

    return stream;
}

//Функция ParseDate
Date ParseDate(istream& stream){
    int value_y, value_m, value_d;

    stream >> value_y;
    stream.ignore(1);
    stream >> value_m;
    CheckValueFormat(value_m, "Month");
    stream.ignore(1);
    stream >> value_d;
    CheckValueFormat(value_d, "Day");

    Date date(value_y, value_m, value_d);

    return date;
}