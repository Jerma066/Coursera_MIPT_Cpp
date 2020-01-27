#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure{
public:
	Triangle(const double& a, const double& b, const double& c) 
		: _a(a), _b(b), _c(c) {
	}
	
    string Name() const override {
        return "TRIANGLE";
    }
	
	double Perimeter() const override{
		return _a + _b + _c;
	}
	
	double Area() const override{
		double hp = (this->Perimeter() / 2);
        return sqrt(hp * (hp - _a) * (hp - _b) * (hp - _c));
	}
		
private:
	double _a, _b, _c;
};

class Rect : public Figure{
public:
	Rect(const double& x, const double& y) 
		: _x(x), _y(y){
	}
	
    string Name() const override {
        return "RECT";
    }
	
	double Perimeter() const override{
		return (_x + _y) * 2;
	}
	
	double Area() const override{
        return _x * _y;
	}
		
private:
	double _x, _y;
};

class Circle : public Figure{
public:
	Circle(const double& r) 
		: _r(r){
	}
	
    string Name() const override {
        return "CIRCLE";
    }
	
    double Perimeter() const override {
        return 2 * 3.14 * _r;
    }
    
    double Area() const override {
        return 3.14 * _r * _r;
    }
		
private:
	double _r;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string type_name;
    is >> type_name;
    if (type_name == "TRIANGLE") {
		double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } 
    else if  (type_name == "RECT") {
		double x, y;
        is >> x >> y;
        return make_shared<Rect>(x, y);
    } 
    else {
        double r;
        is >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
	vector<shared_ptr<Figure>> figures;
	
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
				<< current_figure->Name() << " "
				<< current_figure->Perimeter() << " "
				<< current_figure->Area() << endl;
			}
		}
	}
	
	return 0;
}
