#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& name = "animal")
		:Name(name){
	}

    const string Name;
};


class Dog : public Animal{
public:
    Dog(const string& name = "dog"):Animal(name) {
	}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};
