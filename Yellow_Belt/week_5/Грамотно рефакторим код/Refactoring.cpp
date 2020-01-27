#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string& name, const string& profession) 
		: _name(name), 
		_profession(profession) {
	}
	
	string Name() const{
        return _name;
    }
    
    string Profession() const{
        return _profession;
    }
    
    string Log() const{
		return (_profession + ": " + _name); 
	}
	
	virtual void Walk(const string& destination) const{
		cout << Log() << " walks to: " << destination << endl;
	}

private:
	const string _name;
	const string _profession;
};

class Student : public Human{
public:
	Student(const string& name, const string& favouriteSong) 
		: Human(name, "Student"), 
		FavouriteSong(favouriteSong) {
	}

    void Learn() const{
        cout<< this->Log() << " learns" << endl;
    }
    
    void SingSong() const {
        cout << this->Log() << " sings a song: " << this->FavouriteSong << endl;
    }

    void Walk(const string& destination) const override {
        cout << this->Log() << " walks to: " << destination << endl;
        SingSong();
    }

public:
    string FavouriteSong;
};


class Teacher : public Human{
public:
    Teacher(const string& name, const string& subject) 
		: Human(name, "Teacher"), 
		Subject(subject) {
	}

    void Teach() const {
        cout << this->Log() << " teaches: " << this->Subject << endl;
    }

public:
    string Subject;
};


class Policeman : public Human{
public:
    Policeman(const string& name) 
		: Human(name, "Policeman") {
    }

    void Check(Human& person) const {
        cout << this->Log() << " checks " << person.Profession() << ". "
             << person.Profession() << "'s name is: " << person.Name() << endl;
    }
};


void VisitPlaces(Human& human, vector<string> places) {
    for (const auto& p : places) {
        human.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
