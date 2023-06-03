/*
Implementation of a direct access file -Insertion and deletion of a record from a Direct Access File.
*/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class HashTable
{
private:
    int empId;          // Employee ID          
    int location;       // Location in the file

public:
    HashTable()
    {
        empId = 0;
        location = 0;
    }
    void createHT();            // Function to initialize the hash table
    void showHT();              // Function to display the hash table
    int Hash(int);              // Hash function to determine the index based on the employee ID
    void insertHT(int, int);    // Function to insert a record into the hash table
    int searchHT();             // Function to search for a record in the hash table
} HT[10];                       // Array of HashTable objects representing the hash table

class MyFile
{
private:
    char buffer[40], fname[10];
    int empId, count;
    string name, address;
    fstream file;
    HashTable HT;

public:
    MyFile()
    {
        empId = 0;
        count = 0;
        name = '\0';
        address = '\0';
        cout << "Enter name of file : ";
        cin >> fname;
    }
    ~MyFile()
    {
        remove("file");
    }
    void writeFile();
    void readFile();
    void searchRecord();
    void deleteRecord();
};

/*
    This function createHT() initializes the hash table by setting 
    the empId and location values of each element in the HT array to 0.
*/

void HashTable ::createHT()
{
    int i, Tablesize = 10;
    for (i = 0; i < Tablesize; i++)
    {
        HT[i].empId = 0;
        HT[i].location = 0;
    }
}

/*
    This function showHT() displays the contents of the hash table. 
    It iterates through the HT array and prints the index, empId, and location values of each element..
*/

void HashTable ::showHT()
{
    int i, Tablesize = 10;

    for (i = 0; i < Tablesize; i++)
    {
        cout << "\n  " << i << HT[i].empId << " " << HT[i].location;
    }
}

/*
    This function Hash() calculates the hash value for a given empId based on the modulo 
    operation with the table size (which is 10 in this case). It returns the calculated hash value.
*/

int HashTable ::Hash(int empId)
{
    int Tablesize = 10;
    return (empId % Tablesize);
}

/*
   This function insertHT() inserts a record into the hash table. It takes the empId and loc (location in the file) 
   as parameters. It first calculates the hash index for the empId. If the location at the calculated index is empty,
   it directly inserts the record. If there is a collision (i.e., the location is already occupied), it uses 
   linear probing to find the next available empty location and inserts the record there.
*/

void HashTable ::insertHT(int empId, int loc)
{
    int index, Tablesize = 10;

    index = Hash(empId);

    if (HT[index].location == 0)
    {
        HT[index].empId = empId;
        HT[index].location = loc;
    }
    else
    {
        do
        {
            index = ((index + 1) % Tablesize);
        } while (HT[index].location != 0);
        HT[index].empId = empId;
        HT[index].location = loc;
    }
}

/*
 This function searchHT() searches for a record in the hash table based on the empId. It prompts the user to 
 enter an empId to search for. It calculates the hash index for the empId and checks 
 if the empId at the calculated index matches the input empId. If they match, it returns the corresponding location. 
 If not, it uses linear probing to find the next index until it finds the matching empId, and then it returns the corresponding location.
*/

int HashTable ::searchHT()
{
    int empId, index, Tablesize = 10;

    cout << "\n\t Enter Employee ID: ";
    cin >> empId;

    index = Hash(empId);

    if (HT[index].empId == empId)
    {
        return HT[index].location;
    }
    else
    {
        do
        {
            index = ((index + 1) % Tablesize);
        } while (HT[index].empId != empId);

        return HT[index].location;
    }
}

/*
 This function writeFile() writes records to the file. It opens the file in output mode (ios::out). 
 If the file opening fails, it displays an error message. Otherwise, it 
 prompts the user to enter the number of records to write. 
 It then takes the employee ID, name, and address for each record from the user and writes them to the file. 
 It also calls HT.insertHT() to insert the employee ID and file location into the hash table.
*/

void MyFile ::writeFile()
{
    file.open(fname, ios::out);

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

/*
 This function searchRecord() searches for a record in the file based on the empId. It opens the file in 
 input mode (ios::in). If the file opening fails, it displays an error message. 
 Otherwise, it calls HT.searchHT() to search for the empId in the hash table and retrieve the corresponding 
 file location. It then seeks to that location in the file, reads the record into the buffer, and displays it as the found record.
*/

void MyFile ::searchRecord()
{
    file.open(fname, ios::in);
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

/*
 This function readFile() reads records from the file and displays them. It opens the file in input mode (ios::in). 
 If the file opening fails, it displays an error message. Otherwise, it reads records from the file using file.getline() 
 until the end of the file is reached. It then displays each record with an index number. 
 After reading the file, it displays the contents of the hash table using HT.showHT().
*/

void MyFile ::readFile()
{
    file.open(fname, ios::in);
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

int main()
{

    MyFile file;

    file.writeFile();

    file.readFile();

    file.searchRecord();

    return 0;
}


// #include<bits/stdc++.h>
// #include<ostream>
// using namespace std;

// class Employee
// {
//     int empID;          // Employee ID          
//     int location;       // Location in the file

//     Employee()
//     {
//         empID = 0;
//         location = 0;
//     }

//     friend class Hashtable;
// };

// class Hashtable
// {
//     Employee *employees;
//     int tableSize;

// public:
//     Hashtable() {
//         // Function to initialize the hash table
//         cout<<"Enter number of employees: ";
//         cin>>tableSize;
//         employees = new Employee[tableSize];

//         for (int i = 0; i < tableSize; i++)
//         {
//             employees[i].empID = 0;
//             employees[i].location = 0;
//         }
//     }

//     void showHT() {
//         // Function to display the hash table
//         for (int i = 0; i < tableSize; i++)
//         {
//             cout << "\n  " << i << employees[i].empID << " " << employees[i].location;
//         }
//     }

//     int Hash(int empID) {
//         // Hash function to determine the index based on the employee ID
//         return empID % tableSize;
//     }

//     void insertHT(int empID, int loc) {
//         // Function to insert a record into the hash table

//         int index;

//         index = Hash(empID);

//         if (employees[index].location == 0)
//         {
//             employees[index].empID = empID;
//             employees[index].location = loc;
//         }
//         else
//         {
//             do
//             {
//                 index = ((index + 1) % tableSize);
//             } while (employees[index].location != 0);
//             employees[index].empID = empID;
//             employees[index].location = loc;
//         }
//     } 

//     int searchHT() {
//         // Function to search for a record in the hash table
//         int empID, index;

//         cout << "\n\t Enter Employee ID: ";
//         cin >> empID;

//         index = Hash(empID);

//         if (employees[index].empId == empID)
//         {
//             return employees[index].location;
//         }
//         else
//         {
//             do
//             {
//                 index = ((index + 1) % tableSize);
//             } while (employees[index].empId != empID);

//             return employees[index].location;
//         }
//     }         
// };

// class MyFile
// {
//     char buffer[40], fname[10];
//     int empId, count;
//     string name, address;
//     fstream file;
//     Hashtable HT;

// public:

//     MyFile()
//     {
//         empId = 0;
//         count = 0;
//         name = '\0';
//         address = '\0';
//         cout << "Enter name of file : ";
//         cin >> fname;

//         ofstream File;
//         File.open(fname);
//         if(File)
//         {
//             cout<<"\nFile opened Successfully";
//             File.close();
//         }
//         else 
//             cout<<"\nFile creation Error";   
//     }

//     ~MyFile()
//     {
//         remove("file");
//     }

//     void writeFile() {
//         file.open(fname, ios::out);

//         if (!file)
//             cout << "\n\nThere is an Error Opening file..." << endl;
//         else
//         {
//             cout << "Enter number of records : ";
//             cin >> count;
//             for (int i = 0; i < count; i++)
//             {
//                 cout << "emp number : ";
//                 cin >> empId;
//                 cout << "Name : ";
//                 cin >> name;
//                 cout << "Address : ";
//                 cin >> address;
//                 cout << "Location : " << file.tellp() << endl;
//                 HT.insertHT(empId, file.tellp());
//                 file << empId << " " << name << " " << address << endl;
//             }
//         }
//         file.close();
//     }

//     void readFile() {
//         file.open(fname, ios::in);
//         if (!file)
//             cout << "\n\nError 404 File Not Found..." << endl;
//         else
//         {
//             int i = 0;
//             while (!file.eof())
//             {
//                 file.getline(buffer, 40);
//                 cout << "Record " << i << " : " << buffer << endl;
//                 i++;
//             }
//         }
//         file.close();
//         cout << "\n\nHash Table : " << endl;
//         HT.showHT();
//     }
    
//     void searchRecord() {
//         file.open(fname, ios::in);
//         if (!file)
//             cout << "\n\nError 404 File Not Found..." << endl;
//         else
//         {
//             int loc = HT.searchHT();
//             file.seekg(loc, ios::beg);
//             file.getline(buffer, 40);
//             cout << "Record Found" << endl
//                 << buffer;
//         }
//         file.close();
//     }
// };
