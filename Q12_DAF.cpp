/*
Implementation of a direct access file -Insertion and deletion of a record from a Direct Access File.
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Employee {
    string name;
    string address;
    int empID;
    int loc;
    
    Employee() {
        name = address = "";
        loc = empID = 0;
    }
    
    bool isEmpty() {
        return empID == 0;
    }
    
    void display() {
        cout<<name<<" "<<address<<" "<<empID<<" "<<loc<<endl;
    }
    
    friend class Hashtable;
    friend class MyFile;
};

class Hashtable {
    Employee *employees;
    int tableSize;
    
    int hash(int empID) {
        return empID % tableSize;
    }
    
public:
    
    Hashtable() {
        cout<<"Enter max number of employees: ";
        cin>>tableSize;
        employees = new Employee[tableSize];
        for(int i=0;i<tableSize;i++) {
            employees[i] = Employee();
        }
    }
    
    void insertHT( Employee emp ) {
        int index = hash(emp.empID);
        if(employees[index].isEmpty()) {
            employees[index] = emp;
        }
        else {
            int curr = index;
            while(!employees[index].isEmpty())
                curr = (curr+1)%tableSize;
            employees[curr] = emp;
        }
    }
    
    void showHT() {
        for(int i=0;i<tableSize;i++) {
            cout.width(7);
            cout<<employees[i].empID;
            cout<<"\t";
            cout.width(5);
            cout<<employees[i].loc<<endl;
        }
    }
    
    void deleteHT(int empID) {
        int index = hash(empID);
        if(employees[index].empID == empID)
            employees[index] = Employee();
        else {
            int curr = index;
            while( employees[index].empID != empID)
                curr = (curr+1)%tableSize;
            employees[curr] = Employee();
        }
    }
    
    int searchHT(int empID) {
        int index = hash(empID);
        if(employees[index].empID == empID) {
            return employees[index].loc;
        }
        else {
            int curr = index, passes = 0;
            while( employees[index].empID != empID and passes != tableSize) {
                curr = (curr+1)%tableSize;
                passes++;
            }
            if(passes != tableSize)
                return employees[curr].loc;
            else
                return  -1;
        }
    }
};

class MyFile {
    char buffer[40], filename[20];
    fstream file; int empCount;
    Hashtable table;
    Employee E;
    
public:
    
    MyFile() {
        cout<<"Enter file name: ";
        cin>>filename;
        
        file.open(filename, ios::out);
        if(file)
            cout<<"File opened successfully"<<endl;
        else
            cout<<"Error in file opening"<<endl;
        file.close();
    }
    
    void addRecord() {
        file.open(filename, ios::app);
        if(file) {
            cout<<"Enter employee name: ";
            cin>>E.name;
            cout<<"Enter employee ID: ";
            cin>>E.empID;
            cout<<"Enter employee address: ";
            cin>>E.address;
            cout<<"Location: "<<file.tellp()<<endl;
            E.loc = file.tellp();
            table.insertHT(E);
            file.write(reinterpret_cast<char*>(&E), sizeof(E));
        }
        else {
            cout<<"Error";
        }
        file.close();
    }
    
    void readRecord() {
        file.open(filename, ios::in);
        if(!file)
            cout<<"Error opening file"<<endl;
        else {
            int empID;
            cout<<"Enter employee ID to read: ";
            cin>>empID;
            int loc = table.searchHT(empID);
            if(loc == -1)
                cout<<"No such record exists."<<endl;
            else {
                file.seekg(loc, ios::beg);
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                E.display();
            }
            cout<<"\nRecord deleted!"<<endl;
        }
        file.close();
    }
    
    void deleteRecord() {
        int empID;
        fstream temp;
        temp.open("temp", ios::app);
        cout<<"Enter the employee ID to delete: ";
        cin>>empID;
        int loc = table.searchHT(empID);
        if(loc == -1)
            cout<<"No such record exists to delete"<<endl;
        else {
            file.open(filename, ios::in);
            while(!file.eof()) {
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                if(E.empID == empID)
                    continue;
                E.loc = temp.tellp();
                temp.write(reinterpret_cast<char*>(&E), sizeof(E));
            }
            file.close();
            temp.close();
            remove(filename);
            rename("temp", filename);
            table.deleteHT(empID);
        }
    }
};

int main() {
    MyFile File;
    File.addRecord();
    File.addRecord();
    File.addRecord();
    File.addRecord();
    
    File.readRecord();
    
    File.deleteRecord();
    
    File.readRecord();
    return 0;
}
