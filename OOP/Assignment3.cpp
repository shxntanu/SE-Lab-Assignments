/*
 * Assignment3.cpp
 *
 *  Created on: Sep 23, 2022
 *      Author: Shantanu
 */

#include<iostream>
#include<string>
using namespace std;

class Publication{
	public:
		string title;
		float price;

	public:
		Publication(){

			//Default Constructor sets inital values to default blank values

			title="";
			price=0.0;
		}

		void setData(){

			//Base Class function to input title and price of item

			cout<<"Enter name of Publication: "<<endl;
			cin>>title;
			try{

				//Exception handling block

				cout<<"Enter price of item: "<<endl;
				cin>>price;
				if(price<0){
					throw price;
				}		
			}

			catch(float p){

				//Catches the exception and resets all member values of Base Class to default

				cout<<"An exception occurred! Resetting all values to default!"<<endl;
				title="";
				price=0.0;
			}
		}

};

class Book : public Publication{

	int pgcnt;

	public:
		Book(){
			pgcnt=0;
		}

		void bookData(){
			setData();
			cout<<"Enter number of pages in book:"<<endl;
			try{
				cin>>pgcnt;
				if(pgcnt<0){
					throw pgcnt;
				}
			}
			catch(int p){

				//Catches the exception and resets all member values of Book class to default

				cout<<"An exception occurred! Resetting all values to default!"<<endl;
				title="";
				price=0.0;
				pgcnt=0;

			}
		}
		public:
		void displayBook(){

			cout<<"\nPublication: "<<title<<"\nPrice: "<<price<<"\nPages: "<<pgcnt<<endl;
		}

};

class Tape : public Publication{

	float time;

	public:
		Tape(){
			time=0.0;
		}

		void tapeData(){
			setData();
			cout<<"Enter the number of minutes the tape plays (float): "<<endl;
			try{
				cin>>time;
				if(time<0){
					throw time;
				}
			}
			catch(float t){

				//Catches the exception and resets all member values to default

					cout<<"An exception occurred! Resetting all values to default!"<<endl;
					title="";
					price=0.0;
					time=0.0;

			}
		}
	    public:
		void displayTape(){

				cout<<"\nPublication: "<<title<<"\nPrice: "<<price<<"\nTime: "<<time<<endl;
		}

};

int main(){

	Book b;
	b.bookData();
	Tape t;
	t.tapeData();
	b.displayBook();
	t.displayTape();

	return 0;
}
