/*
Author - Shantanu Wable

Department maintains a student information file. The file contains roll number, name, division and address.
Allow user to add, delete information of student. Display information of particular student.
If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use Sequential File to maintain the data.
*/

#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int roll, div;
    string name, address;
    
    Student() {
        roll = div = 0;
        name = address = "";
    }
    
    void display() {
        cout<<name<<" "<<roll<<" "<<div<<" "<<address<<endl;
    }
    
    void getData() {
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter roll no: ";
        cin>>roll;
        cout<<"Enter div: ";
        cin>>div;
        cout<<"Enter address: ";
        cin>>address;
    }
    
    friend class MyFile;
};

class MyFile {
    char filename[20];
    fstream file;
    Student S;
    
public:
    
    MyFile() {
        cout<<"Enter filename: ";
        cin>>filename;
        file.open(filename, ios::out);
        if(file)
            cout<<"File opened successfully."<<endl;
        else
            cout<<"File opening error."<<endl;
        file.close();
    }
    
    void addRecord() {
        file.open(filename, ios::app);
        S.getData();
        file.write(reinterpret_cast<char*>(&S), sizeof(S));
        file.close();
    }
    
    void displayRecords() {
        file.open(filename, ios::in);
        file.read(reinterpret_cast<char*>(&S), sizeof(S));
        while(!file.eof()) {
            S.display();
            file.read(reinterpret_cast<char*>(&S), sizeof(S));
        }
        file.close();
    }
    
    void deleteRecord(int roll) {
        file.open(filename, ios::in);
        fstream temp;
        temp.open("temp", ios::out);
        bool found = false;
        file.read(reinterpret_cast<char*>(&S), sizeof(S));
        while(!file.eof()) {
            if(roll == S.roll) {
                cout<<"Deleting: ";
                S.display();
                found = true;
            }
            else
                temp.write(reinterpret_cast<char*>(&S), sizeof(S));
            file.read(reinterpret_cast<char*>(&S), sizeof(S));
        }
        
        if(!found)
            cout<<"No such data exists."<<endl;
        
        file.close();
        temp.close();
        remove(filename);
        rename("temp", filename);
    }
};

int main() {
    MyFile File;
    int Choice;
    int R;
    do {
        cout<<"\n1: Add a record\n2: Display Database\n3: Delete a record\nEnter your choice: ";
        cin>>Choice;

        switch( Choice ) {
            case 1:
                File.addRecord();
                break;
                    
            case 2:
                File.displayRecords();
                break;
                    
            case 3:
                cout<<"Enter the record you want to delete: ";
                cin>>R;
                File.deleteRecord(R);
                break;
        }
    }
    while(Choice<6);
    cout<<endl;
    return 0;
}
