#include <iostream>
#include<bits/stdc++.h>
#include<string>
#include<map>
using namespace std;

int main() {
	map<string,int> state_map;
		state_map.insert(make_pair("Maharashtra", 125));
		state_map.insert(make_pair("Tamil Nadu", 80));
		state_map.insert(make_pair("Rajasthan", 78));
		state_map.insert(make_pair("Odisha", 47));
		state_map.insert(make_pair("Kerala", 38));
		state_map.insert(make_pair("Telangana", 37));
		state_map.insert(make_pair("Assam", 35));
		state_map.insert(make_pair("Jharkhand", 38));
		state_map.insert(make_pair("Karnataka", 68));
		state_map.insert(make_pair("Gujarat", 70));
		state_map.insert(make_pair("Punjab", 31));
		state_map.insert(make_pair("Chhattisgarh", 30));
		state_map.insert(make_pair("Haryana", 29));
		state_map.insert(make_pair("Uttarakhand", 12));
		state_map.insert(make_pair("Tripura", 04));
		state_map.insert(make_pair("Meghalaya", 4));
		state_map.insert(make_pair("Manipur", 3));
		state_map.insert(make_pair("Nagaland", 2));
		state_map.insert(make_pair("Goa", 2));
		state_map.insert(make_pair("Mizoram", 1));
		state_map.insert(make_pair("Sikkim", 1));
	string state;
	int m = 1;
	int ch;
	while(m!=0){
		cout<<"Enter the Name of the state : "<<endl;
		cin>>state;
		if(state_map.find(state)!=state_map.end()){
			cout<<"The population of the state "<<state<<" "<<"is : "<<state_map[state]<<" million. "<<endl;
			cout<<"To Check Again Press 1 "<<endl;
			cout<<"To Exit the program Press 2 "<<endl;
			cin>>ch;
			if(ch==1){
				continue;
			}
			if(ch==2){
				cout<<"Exiting the program "<<endl;
				m=0;
			}
		}
		else{
			cout<<"State Not Found ."<<endl;
			cout<<"To Check Again Press 1 "<<endl;
			cout<<"To Exit the program Press 2 "<<endl;
			cin>>ch;
			if(ch==1){
				continue;
			}
			if(ch==2){
				cout<<"Exiting the program "<<endl;
				m=0;
			}
		}
	}
	return 0;
}
