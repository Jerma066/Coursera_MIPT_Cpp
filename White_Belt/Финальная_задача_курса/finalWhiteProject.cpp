//============================================================================
// Name        : finalWhiteProject.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
#include <string.h>

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~ Реализация класса даты и всяческие функции по работе с этим классом ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Date {
public:
	Date(){
		year = 0;
		month = 0;
		day = 0;
	};

	Date(int y, int m, int d){
		year = y;
		month = m;
		day = d;
	}

	int GetYear() const{
		return year;
	}
	int GetMonth() const{
		return month;
	}
	int GetDay() const{
		return day;
	}

	~Date(){};

private:
  int year;
  int month;
  int day;
};

void CheckDateFormat(const string& date){
	stringstream input(date);
	int number;
	char bufSym;

	//По условию уормат года проверять не нужно. Спихнем его в number
	input >> number;

	if(input.peek() == '-'){input.ignore(1);}
	else{throw invalid_argument("Wrong date format: " + date);}

	//Переходим к полю, которое фактически должно быть месяцем
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

	//Переходим к полю, которое фактически должно быть днем
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

//Ввод класса Date
istream& operator>>(istream& stream, Date& date){
	string buffer;

	getline(stream, buffer);
	stringstream input(buffer);
	CheckDateFormat(buffer);

	int value_y, value_m, value_d;
	if(stream){
		//Считываем год
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

//Вывод класса Date
ostream& operator<< (ostream& stream, const Date& date){
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

//Операторы < для работы с контейнером map
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~ Реализация класса даты и всяческие функции по работе с этим классом ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
class Database{
public:
	void AddEvent(const Date& date, const string& event){
		dateBase[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event){
		bool answer = false;

		if((dateBase[date]).count(event) != 0){
			(dateBase[date]).erase(event);
			answer = true;
		}

		return answer;
	}
	int DeleteDate(const Date& date){
		int counter = 0;

		counter = (dateBase[date].size());
		dateBase[date].clear();

		return counter;
	}

	void Find(const Date& date)const{
		set<string>::iterator it;
		if(dateBase.find(date) == dateBase.end()){

		}
		else{
			for(it = (dateBase.at(date)).begin(); it != (dateBase.at(date)).end(); ++it){
				cout << *it << endl;}
		}
	}

	void Print(){
		map<Date, set<string> >::iterator it;
		set<string>::iterator it_s;

		for(it = dateBase.begin(); it != dateBase.end(); it++)
		{
			Date current_Date = (*it).first;
			for(it_s = (dateBase.at(current_Date)).begin(); it_s != (dateBase.at(current_Date)).end(); ++it_s){
						cout << current_Date << ' ' << *it_s << endl;
			}
		}
	}

private:
	map<Date, set<string> > dateBase;
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

int main() {

	Database db;
	string command;

	try{

		while(getline(cin, command)){
			stringstream input(command);
			string keyWord;

			//~~~~~~~~~~~~~~считывание ключевого слова команды~~~~~~~~~~~~~~~~//
			int spaceN;
			spaceN = count(command.begin(), command.end(), ' ');
			if(spaceN != 0){getline(input, keyWord, ' ');}
			else{keyWord = command;}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

			if(keyWord == "Add"){
				//~~~заполнение даты без ущерба для остального потока~~~//
				Date date;
				string dateString;

				getline(input, dateString, ' ');
				stringstream dateStream(dateString);
				dateStream >> date;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

				//~~~заполнения поля событие ~~~~~~~~~~~~~~~~~~~~~~~~~~~//
				string event;
				input >> event;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

				db.AddEvent(date, event);
			}
			else if(keyWord == "Del"){
				//Узнаем, что за коммнада введена (есть ли в ней поле event или нет)~~~//
				int spaceNum;
				spaceNum = count(command.begin(), command.end(), ' ');
				//~~~~(если 1, то удалаем все элементы; 2 - считываем event)~~~~~~~~~~~//

				Date date;
				if(spaceNum == 1){
					input >> date;
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
				}
				else if(spaceNum == 2){
					//~~~заполнение даты без ущерба для остального потока~~~//
					Date date;
					string dateString;

					getline(input, dateString, ' ');
					stringstream dateStream(dateString);
					dateStream >> date;
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

					//~~~заполнения поля событие ~~~~~~~~~~~~~~~~~~~~~~~~~~~//
					string event;
					input >> event;
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

					if(db.DeleteEvent(date, event)){
						cout << "Deleted successfully" << endl;
					}
					else{
						cout << "Event not found" << endl;
					}
				}
			}
			else if(keyWord == "Find"){
				Date date;

				input >> date;
				db.Find(date);
			}
			else if(keyWord == "Print"){
				db.Print();
			}
			else if(command == ""){
			}
			else{
				throw invalid_argument("Unknown command: " + keyWord);
			}
		}

	}catch(invalid_argument& e1){
		cout << e1.what() << endl;
		return 1;
	}catch(exception& e2){
		cout << e2.what() << endl;
		return 2;
	}

	return 0;
}
