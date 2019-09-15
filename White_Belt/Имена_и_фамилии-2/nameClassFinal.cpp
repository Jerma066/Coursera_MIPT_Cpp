//============================================================================
// Name        : nameClassFinal.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

string getName(map<int, string> name_map, int year){
	  string answer;

	  map<int,string>::iterator it;

	  for(it = name_map.begin(); it != name_map.end(); ++it) {
		  if(it->first <= year){
			  answer = it ->second;
		  }
		  else{
			  break;
		  }
	  }

	  return answer;
 }

string fillFullName(map<int, string> name_map, int year, string type){
	  vector<string> fullHistory;
	  string answer;

	  map<int,string>::iterator it;
	  string prevName;

	  for(it = name_map.begin(); it != name_map.end(); ++it) {
		  if(it->first <= year && it->second != prevName){
			  fullHistory.push_back(it->second);
			  prevName = it->second;
		  }
		  else{
			  break;
		  }
	  }

	  reverse(fullHistory.begin(), fullHistory.end());

	  if(!fullHistory.empty()){
		  for(int i = 0; i < fullHistory.size(); i++)
		  {
			  if(i == 0){
				  answer = fullHistory[i];
			  }
			  else if(i == 1){
				  answer += " (" + fullHistory[i];
			  }
			  else{
				  answer += ", " +  fullHistory[i];
			  }
		  }
		  if(fullHistory.size() > 1){
			  answer += ")";
		  }
	  }


	  return answer;
  }

class Person {
public:
    Person(string new_first_name, string new_last_name, int new_birthyear){
    	year_of_birth = new_birthyear;
        first_names[new_birthyear] = new_first_name;
        last_names[new_birthyear] = new_last_name;
    }
    Person() {};
  void ChangeFirstName(int year, const string& first_name) {
	  if( year >= year_of_birth){
		  first_names[year] = first_name;
	  }
  }
  void ChangeLastName(int year, const string& last_name) {
	  if(year >= year_of_birth){
		  last_names[year] = last_name;
	  }
  }

  string GetFullName(int year) const{

	if(year < year_of_birth){
		return "No person";
	}

    // получаем имя и фамилию по состоянию на год year
    const string first_name = getName(first_names, year);
    const string last_name = getName(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  string GetFullNameWithHistory(int year) const {

	if(year < year_of_birth)
	{
		return "No person";
	}

	const string firstName = fillFullName(first_names, year, "first");
  	const string lastName = fillFullName(last_names, year, "last");

    // если и имя, и фамилия неизвестны
    if (firstName.empty() && lastName.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (firstName.empty()) {
      return lastName + " with unknown first name";

    // если неизвестна только фамилия
    } else if (lastName.empty()) {
      return firstName + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return firstName + " " + lastName;
    }
  }

private:

  int year_of_birth;

  map<int, string> first_names;
  map<int, string> last_names;


};

int main(){
	  Person person("Polina", "Sergeeva", 1960);

	  cout << person.GetFullNameWithHistory(1959) << endl;
	  cout << person.GetFullNameWithHistory(1960) << endl;

	  person.ChangeFirstName(1965, "Appolinaria");
	  person.ChangeLastName(1967, "Ivanova");

	  cout << person.GetFullNameWithHistory(1965) << endl;
	  cout << person.GetFullNameWithHistory(1967) << endl;


	  return 0;

}
