//============================================================================
// Name        : drobi1task.cpp
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

//���������� �����
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

//����� � �������
	void znak()
	{
		if (ch == 0) {zn = 1;}
		if ((zn < 0) && (ch < 0)) { ch = abs(ch); zn = abs(zn);}
		if ((zn < 0) && (ch > 0)) { ch = -1*ch; zn = abs (zn);}
	}

//����� ����� (����� ����� ������ ����� ��������������� ��������� <<)
	void vivod() const
	{
		cout<< ch <<"/"<< zn << endl;
	}

//�������� ��������
	Rational operator + (const Rational sl)   const
	{
		return Rational (ch*sl.zn + sl.ch*zn, zn*sl.zn);
	}

//�������� ���������
	Rational operator - (const Rational vi)   const
	{
		return Rational (ch*vi.zn - vi.ch*zn, zn*vi.zn);
	}

//�������� ���������
	Rational operator * (const Rational mn)   const
	{
		return Rational (ch*mn.ch, zn*mn.zn);
	}

//�������� �������
	Rational operator / (const Rational del)   const
	{
		return Rational (ch*del.zn, zn*del.ch);
	}

//�������� ���������
	int operator == (const Rational sr)   const
	{
		if ((ch == sr.ch) && (zn == sr.zn)) {return(1);}
					else {return(0);}
	}


//��������� ��������� ��� ������ map ����������
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
int main()
{
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }
    cout << "OK" << endl;

	return 0;
}

