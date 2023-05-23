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
    int empId;
    int location;

public:
    HashTable()
    {
        empId = 0;
        location = 0;
    }
    void createHT();
    void showHT();
    int Hash(int);
    void insertHT(int, int);
    int searchHT();
} HT[10];

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

void HashTable ::createHT()
{
    int i, Tablesize = 10;
    for (i = 0; i < Tablesize; i++)
    {
        HT[i].empId = 0;
        HT[i].location = 0;
    }
}

void HashTable ::showHT()
{
    int i, Tablesize = 10;

    for (i = 0; i < Tablesize; i++)
    {
        cout << "\n  " << i << HT[i].empId << " " << HT[i].location;
    }
}

int HashTable ::Hash(int empId)
{
    int Tablesize = 10;
    return (empId % Tablesize);
}

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
