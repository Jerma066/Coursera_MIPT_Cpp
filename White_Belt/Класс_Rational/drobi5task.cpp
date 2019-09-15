//============================================================================
// Name        : drobi5task.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <set>
#include <vector>
using namespace std;

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

istream& operator>>(istream& stream, Rational& r) {
	long long x, y;
	if (stream) {
		stream >> x;
		stream.ignore(1);
		stream >> y;
		Rational r1(x, y);
		r = r1;
	}
	stream.ignore(1);
	return stream;
}


ostream& operator<<(ostream& stream, const Rational& r) {
	stream << r.Numerator();
	stream << "/";
	stream << r.Denominator();
	return stream;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
