#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Student
{
    string name ,cls, bldgrp, add, drvlic,dob;
	int rno;
	long tele;

    public:
        Student() //Default Constructor
        {
            name=""; cls="";bldgrp="";add="";drvlic="";dob="";
            rno=0; tele=0;
        }

        Student(string name, string cls, string bldgrp, string add, string drvlic, string dob, int rno, int tele, int aadhaar)
        {
        	this->name = name;
        	this->cls = cls;
        	this->bldgrp = bldgrp;
        	this->add = add;
        	this->drvlic = drvlic;
        	this->dob = dob;
        	this->rno = rno;
        	this->tele = rno;
        }

	    Student(const Student &s1) //Copy Constructor
	    {
	        name = s1.name;
	        cls = s1.cls;
	        bldgrp = s1.bldgrp;
	        add = s1.add;
	        drvlic = s1.drvlic;
	        dob = s1.dob;
	        rno = s1.rno;
	        tele = s1.tele;
	    }

	public:
	    void input()
	    {
	        cout<<"Enter Name: ";
			cin>>name;
			cout<<"\nEnter Class: ";
			cin>>cls;
			cout<<"\nEnter Blood Group: ";
			cin>>bldgrp;
			cout<<"\nEnter Address: ";
			cin>>add;
			cout<<"\nEnter Driving licence no: ";
			cin>>drvlic;
			cout<<"\nEnter Date of birth: ";
			cin>>dob;
			cout<<"\nEnter roll no: ";
			cin>>rno;
			cout<<"\nEnter Telephone No: ";
			cin>>tele;
			cout<<"\n\n\n\n";
	    }

	public:
		inline void display()
		{
			cout<<left<<setw(30)<<name<<setw(30)<<cls<<setw(30)<<bldgrp<<setw(30)<<add<<setw(30)<<drvlic<<setw(30)<<dob<<setw(30)<<rno<<setw(30)<<tele<<endl;
		}

		~ Student() //Destructor
		{
			cout<<"Destructor Invoked"<<endl;
		}

    friend class Hello;
};

class Hello
{
    public:
        Hello(){
            cout<<"Hello"<<endl;
        }

        void display(Student &s)
        {
            cout<<"Name: "<<s.name<<endl;
        }

        ~Hello(){
            cout<<"Bye!";
        }
};

int main()
{
	Student s1,s2,s3,s4;
	s1.input();
	s2.input();
	s3.input();
	s4.input();
	cout<<left<<setw(30)<<"NAME"<<setw(30)<<"CLASS"<<setw(30)<<"BLOOD GROUP"<<setw(30)<<"ADDRESS"<<setw(30)<<"DRIVING LIC NO"<<setw(30)<<"DATE OF BIRTH"<<setw(30)<<"ROLL NO"<<setw(30)<<"TELEPHONE"<<"\n============================================================================================="<<endl;
	s1.display();
	s2.display();
	s3.display();
	s4.display();
	Hello *h = new Hello[3];
	delete [] h;
}
