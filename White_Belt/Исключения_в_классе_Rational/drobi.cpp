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
		    if (denumerator == 0) {
		    	throw invalid_argument("invalid_argument");
		    }
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
		if(del.ch == 0)
		{
			throw domain_error("domain_error");
		}
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

int main()
{
	/*
	int ch1, zn1, ch2, zn2;

	cout <<"введите числитель 1-ой дроби" << endl;
	cin >> ch1;
	cout << "введите знаменатель 1-ой дроби" << endl;
	cin >> zn1;

	cout <<"введите числитель 2-ой дроби (Не ноль! На ноль делить нельзя)" << endl;
	cin >> ch2;
	cout << "введите знаменатель 2-ой дроби" << endl;
	cin >> zn2;


	Rational a(ch1, zn1);
	Rational b(ch2, zn2);

	a.vivod();
	b.vivod();
	cout << "сложение =  ";
	(a+b).vivod();
	cout << "вычитание (из первого второе) = ";
	(a-b).vivod();
	cout << "умножение =  ";
	(a*b).vivod();
	cout << "деление (первого на второе) = ";
	(a/b).vivod();
	cout << "сравнение чисел (1 - равные; 0 - разные)= " << (a == b) << endl;


	map<Rational,string> M;
	cout << "дробь номер 1 = "; a.vivod();
	cin >> M[a];

	cout << "дробь номер 2 = "; b.vivod();
	cin >> M[b];


	cout << M[a] << " " << M[b];
	cout << endl;

	*/


    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument& e) {
    	cout << e.what() << endl;
    }


    try {
        Rational x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error& e) {
    	cout << e.what() << endl;
    }


    cout << "OK" << endl;
    return 0;
}	
	

