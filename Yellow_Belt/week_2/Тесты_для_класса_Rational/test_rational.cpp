#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Rational {
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
	
	
private:
	int ch;
	int zn;
};


//Собственно тесты

void TestRationalInit() {
    const Rational r(3, 10);
    
    AssertEqual(r.Numerator(), 3);
    AssertEqual(r.Denominator(), 10);
}

void TestPureInitRationalTets(){
	/*const*/ Rational r;
	
	AssertEqual(r.Numerator(), 0);
	AssertEqual(r.Denominator(), 1);
}

void TestReductionInitRational(){
	const Rational r(15, 25);
	
	AssertEqual(r.Numerator(), 3);
	AssertEqual(r.Denominator(), 5);
}

void TestNegativeNumeratorInitRtional(){
	const Rational r(-1, 3);
	
	AssertEqual(r.Numerator(), -1);
	AssertEqual(r.Denominator(), 3);
}

void TestNegativeDenominatorInitRtional(){
	const Rational r(1, -3);
	
	AssertEqual(r.Numerator(), -1);
	AssertEqual(r.Denominator(), 3);
}

void TestBothNegativeInitRational(){
	const Rational r(-1, -3);
	
	AssertEqual(r.Numerator(), 1);
	AssertEqual(r.Denominator(), 3);
}

void TestZeroNumeratorInitRational(){
	const Rational r(0, 228);
	
	AssertEqual(r.Numerator(), 0);
	AssertEqual(r.Denominator(), 1);
}



int main(){
  TestRunner runner;
  
  runner.RunTest(TestRationalInit, "TestRationalInit");
  runner.RunTest(TestPureInitRationalTets, "TestPureInitRationalTets");
  runner.RunTest(TestReductionInitRational, "TestReductionInitRational");
  runner.RunTest(TestNegativeNumeratorInitRtional, "TestNegativeNumeratorInitRtional");
  runner.RunTest(TestNegativeDenominatorInitRtional, "TestNegativeDenominatorInitRtional");
  runner.RunTest(TestBothNegativeInitRational, "TestBothNegativeInitRational");
  runner.RunTest(TestZeroNumeratorInitRational, "TestZeroNumeratorInitRational");
  
  return 0;
}
