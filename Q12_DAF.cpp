/*
Implementation of a direct access file -Insertion and deletion of a record from a Direct Access File.
*/

#include<bits/stdc++.h>
using namespace std;

class Employee {
    int empID;          // Employee ID
    int location;       // Location in the file

    Employee()
    {
        empID = 0;
        location = 0;
    }

    friend class Hashtable;
};

class Hashtable {
    Employee *employees;
    int tableSize;

public:
    Hashtable() {
        // Function to initialize the hash table
        cout<<"Enter number of employees: ";
        cin>>tableSize;
        employees = new Employee[tableSize];

        for (int i = 0; i < tableSize; i++)
        {
            employees[i].empID = 0;
            employees[i].location = 0;
        }
    }

    void showHT() {
        // Function to display the hash table
        for (int i = 0; i < tableSize; i++)
        {
            cout << i+1 << ". " << employees[i].empID << " " << employees[i].location<<endl;
        }
    }

    int Hash(int empID) {
        // Hash function to determine the index based on the employee ID
        return empID % tableSize;
    }

    void insertHT(int empID, int loc) {
        // Function to insert a record into the hash table

        int index;

        index = Hash(empID);

        if (employees[index].location == 0)
        {
            employees[index].empID = empID;
            employees[index].location = loc;
        }
        else
        {
            do
            {
                index = ((index + 1) % tableSize);
            } while (employees[index].location != 0);
            employees[index].empID = empID;
            employees[index].location = loc;
        }
    }

    int searchHT() {
        // Function to search for a record in the hash table
        int empID, index;

        cout << "\n\t Enter Employee ID: ";
        cin >> empID;

        index = Hash(empID);

        if (employees[index].empID == empID)
        {
            return employees[index].location;
        }
        else
        {
            do
            {
                index = ((index + 1) % tableSize);
            } while (employees[index].empID != empID);

            return employees[index].location;
        }
    }
};

class MyFile
{
    char buffer[40], fileName[10];
    int empId, count;
    string name, address;
    fstream file;
    Hashtable HT;

public:

    MyFile()
    {
        empId = 0;
        count = 0;
        name = '\0';
        address = '\0';
        cout << "Enter name of file : ";
        cin >> fileName;

        ofstream File;
        File.open(fileName);
        if(File)
        {
            cout<<"\nFile opened Successfully"<<endl;
            File.close();
        }
        else
            cout<<"\nFile creation Error"<<endl;
    }

    ~MyFile()
    {
        remove("file");
    }

    void writeFile() {
        file.open(fileName, ios::out);

        if (!file)
            cout << "\n\nThere is an Error Opening file..." << endl;
        else
        {
            cout << "Enter number of records : ";
            cin >> count;
            for (int i = 0; i < count; i++)
            {
                cout << "emp number : ";
                cin >> empId;
                cout << "Name : ";
                cin >> name;
                cout << "Address : ";
                cin >> address;
                cout << "Location : " << file.tellp() << endl;
                HT.insertHT(empId, file.tellp());
                file << empId << " " << name << " " << address << endl;
            }
        }
        file.close();
    }

    void readFile() {
        file.open(fileName, ios::in);
        if (!file)
            cout << "\n\nError 404 File Not Found..." << endl;
        else
        {
            int i = 0;
            while (!file.eof())
            {
                file.getline(buffer, 40);
                cout << "Record " << i << " : " << buffer << endl;
                i++;
            }
        }
        file.close();
        cout << "\n\nHash Table : " << endl;
        HT.showHT();
    }

    void searchRecord() {
        file.open(fileName, ios::in);
        if (!file)
            cout << "\n\nError 404 File Not Found..." << endl;
        else
        {
            int loc = HT.searchHT();
            file.seekg(loc, ios::beg);
            file.getline(buffer, 40);
            cout << "Record Found" << endl
                 << buffer;
        }
        file.close();
    }
};

int main() {
    MyFile File;

    File.writeFile();
    File.readFile();
    File.searchRecord();
    return 0;
}
