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
    
    void nukeHT() {
        for(int i=0;i<tableSize;i++)
            employees[i] = Employee();
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
    
    void updateEntry(int empID, int newLoc) {
        int index = hash(empID);
        if(employees[index].empID == empID)
            employees[index].loc = newLoc;
        else {
            int curr = index;
            while( employees[index].empID != empID )
                curr = (curr+1)%tableSize;
            employees[curr].loc = newLoc;
        }
    }
};

class MyFile {
    char filename[20];
    fstream file;
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
    
    void addRecord(string n, int id, string a) {
        file.open(filename, ios::app);
        if(file) {
            E.name = n;
            E.empID = id;
            E.address = a;
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
    
    void readRecord(int empID) {
        file.open(filename, ios::in);
        if(!file)
            cout<<"Error opening file"<<endl;
        else {
            int loc = table.searchHT(empID);
            if(loc == -1)
                cout<<"No such record exists."<<endl;
            else {
                file.seekg(loc, ios::beg);
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                E.display();
            }
        }
        file.close();
    }
    
    void deleteRecord(int empID) {
        int loc = table.searchHT(empID);
        if(loc == -1)
            cout<<"No such record exists to delete"<<endl;
        else {
            fstream temp;
            temp.open("temp", ios::out);
            file.open(filename, ios::in);
            while(!file.eof()) {
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                if(E.empID == empID) {
                    cout<<"Deleting Record"<<endl;
                }
                else {
                    E.loc = temp.tellp();
                    table.updateEntry(E.empID, E.loc);
                    temp.write(reinterpret_cast<char*>(&E), sizeof(E));
                }
            }
            file.close(); temp.close();
            remove(filename);
            rename("temp", filename);
            table.deleteHT(empID);
            cout<<"\nRecord deleted!"<<endl;
        }
    }
};

int main() {
    MyFile File;
    File.addRecord("Durvesh", 21381, "Mumbai");
    File.addRecord("Shantanu", 21382, "Pune");
    File.addRecord("Riya", 21383, "Nasik");
    File.addRecord("Atharva", 21384, "Baner");
    File.addRecord("Aarti", 21385, "Balewadi");
    File.addRecord("Riddhi", 21467, "Hadapsar");
    
    File.readRecord(21383);
    
    File.deleteRecord(21384);
    
    File.readRecord(21467);
    File.readRecord(21384);
    
    return 0;
}
