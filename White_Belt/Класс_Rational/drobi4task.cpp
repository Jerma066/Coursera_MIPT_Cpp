//============================================================================
// Name        : drobi4task.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <map>
#include <string>

using namespace std;

class Rational{
	public:
		Rational()
		{
			ch = 0;
			zn = 1;
		}

		Rational (int numerator, int denumerator)
		{
    		  ch = numerator;
    		  zn = denumerator;
		  znak();
		  nod();
  		}

		int Numerator() const {
			return ch;
		}

		int Denominator() const {
			return zn;
		}

		~Rational(){};

//Сокращение дроби
	void nod()
	{
		int c, i, a, b;
		a = abs(ch);
		b = abs(zn);
		if (a>b) {c=a; a=b; b=c;}
		if ((a==0) || (b==0)) {c=1;}
		  else{
			for (i=a; i>=0; i--) {
				if ((a%i == 0) && (b%i == 0)) {
					c=i;
					break;
			}
		      }
		}


		ch = ch/c;
		zn = zn/c;
	}

//Знаки и условия
	void znak()
	{
		if (ch == 0) {zn = 1;}
		if ((zn < 0) && (ch < 0)) { ch = abs(ch); zn = abs(zn);}
		if ((zn < 0) && (ch > 0)) { ch = -1*ch; zn = abs (zn);}
	}

//Вывод Дроби (Нужно будет сдеать через переопределение оператора <<)
	void vivod() const
	{
		cout<< ch <<"/"<< zn << endl;
	}

//Оператор сложения
	Rational operator + (const Rational sl)   const
	{
		return Rational (ch*sl.zn + sl.ch*zn, zn*sl.zn);
	}

//Оператор вычитания
	Rational operator - (const Rational vi)   const
	{
		return Rational (ch*vi.zn - vi.ch*zn, zn*vi.zn);
	}

//Оператор умножения
	Rational operator * (const Rational mn)   const
	{
		return Rational (ch*mn.ch, zn*mn.zn);
	}

//Оператор деления
	Rational operator / (const Rational del)   const
	{
		return Rational (ch*del.zn, zn*del.ch);
	}

//Оператор равенства
	int operator == (const Rational sr)   const
	{
		if ((ch == sr.ch) && (zn == sr.zn)) {return(1);}
					else {return(0);}
	}

//Операторы сравнения для работы map контейнера
	bool operator< (const Rational A) const
	{
		return (ch * A.zn) < (zn * A.ch);
	}

	bool operator> (const Rational A) const
	{
		return (ch * A.zn) > (zn * A.ch);
	}


	private:
		int ch;
		int zn;


};

//Реализация ввода и вывода
ostream& operator << (ostream& stream, const Rational& r){
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}
istream& operator >> (istream& stream, Rational& r){
	char delenie;
	int a, b;
	stream >> a >> delenie >> b;
	if (stream && delenie == '/') {
		r = {a, b};
	}
	return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
