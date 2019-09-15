#include <iostream>
#include <map>
#include <vector>

using namespace std;

void BUSES_FOR_STOP(map<string, vector<string> > &m, vector<string>  &vect, string stop){
    int sum = 0;
			
	for(auto temp: vect){
		for(auto j: m[temp]){
			
            if(j == stop){
                cout << temp << " ";
                ++sum;
            }
		}
	}
    if(sum==0){
        cout << "No stop" << endl;
    }
	cout << endl;
}

void STOPS_FOR_BUS(map<string, vector<string> > &m, vector<string> &vect, string bus){
    
    for(auto j: m[bus]){
        int sum = 0;
        cout << "Stop " << j << ": ";
        for(auto i: vect){
            
            for(auto k: m[i]){
                if( (i!= bus) && (k==j) ){
                    cout << i << " " ;
                    ++sum;
                }
            }
            
        }
        if(sum == 0) cout << "no interchange " << endl;
        else cout << endl;
    }
  

}

void ALL_BUSES(map<string, vector<string> > &m, vector<string> &vect){
    if(m.size()==0) cout << "No buses" << endl;
    else{
        for(auto i: m){
            cout << "Bus " << i.first << ": ";
            for(auto k: i.second){
                cout << k << " ";
                
            }
            cout << endl;
            
        }
            
    }
} 

int main(){
	map<string, vector<string> > m;
	vector<string> vect;
	int Q;
	cin >> Q;
	int i = 0;
	while(i<Q){
		string s;
		cin >> s;
		if(s == "NEW_BUS"){
			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			vector<string> v1(stop_count);
			for(int j=0; j<stop_count; j++){
               
				cin >> v1[j];
                		//cout << (m(bus))[j] << endl;
			}	
			m[bus] = v1;
			vect.push_back(bus);

		}
		else if(s == "BUSES_FOR_STOP"){
			string stop;
			cin >> stop;
			BUSES_FOR_STOP(m, vect, stop);
		}
		else if(s == "STOPS_FOR_BUS"){
            
            		string s;
            		cin >> s;
            		auto search = m.find(s);
            		if(search==m.end()){
               			cout << "No bus" << endl;
            		}
            		else{
                		STOPS_FOR_BUS(m, vect, s);
            		}
		}
		else if(s == "ALL_BUSES"){
            		ALL_BUSES(m, vect);
		}
		else cout << "mistake" << endl;

		++i;
	}

	return 0;
}
