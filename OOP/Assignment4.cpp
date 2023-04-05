/*
 * File_Handling.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: Shantanu
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
{
	public:
		string name; int rno;

	public:
		void input()
		{
			cout<<"Enter Roll Number: ";
			cin>>rno;
			cout<<endl<<"Enter Name: ";
			cin>>name;
			cout<<endl;
		}

		void display()
		{
			cout<<"Name: "<<name<<endl;
			cout<<"Roll Number: "<<rno<<endl;
		}
};

int main()
{
	fstream file;
	file.open("sample.txt",ios::out);

	int n;
	cout<<"Enter Number of students: ";
	cin>>n;
	cout<<endl;

	Student s[n];

	for(int i=0;i<n;i++)
	{
		s[i].input();
		file<<"Name: "<<s[i].name<<endl<<"Roll Number: "<<s[i].rno<<endl;
	}

	file.close();

	string line;

	file.open("sample.txt");
	while(!file.eof())
	{
		file>>line;
		cout<<line;
	}

	return 0;
}
