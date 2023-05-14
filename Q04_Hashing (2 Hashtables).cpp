/*
Author - Shantanu Wable

Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two collision
handling techniques and compare them using number of comparisons required to find a
set of telephone numbers
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Client {

    char name[20];
    ll phone;

public:

    Client() { 
        strcpy( name , "----" ) ;
        phone = 0 ;
    }

    void printDetails() {
		cout.width( 20 ) ;
		cout << name << " " ;
		cout.width( 20 ) ;
		cout << phone << "\n" ;
	}

    Client( char n[] , ll telephone ) {
        strcpy( name , n ) ;
        phone = telephone ;
    }

    bool isEmpty(){
        return phone == 0;
    }

    friend class Hashtable;
};

class Hashtable
{
    int tableSize;
    Client* clients_woReplacement;
    Client* clients_wReplacement;

    int hashfunction( char clientName[] )
    {   
        int n = sizeof(clientName)/sizeof(clientName[0]);
        int sum=0;
        for(int i=0;i<n;i++)
            sum+=i;
        return sum%n;
    }

    bool isOriginal( int index, Client table[] ) {
        return hashfunction( table[index].name ) == index;
    }

public:

    Hashtable(int tableSize) {
        this->tableSize = tableSize;
        clients_woReplacement = new Client[ tableSize ];
        clients_wReplacement = new Client[ tableSize ];
    }

    void createTable() {
        for(int i=0; i<tableSize; i++) {
            clients_woReplacement[ i ] = Client();
            clients_wReplacement[ i ] = Client();
        }
    }

    void insertClient_woReplacement( Client newClient ) {
        int index = hashfunction( newClient.name );
        if( clients_woReplacement[index].isEmpty() ) {
            clients_woReplacement[index] = newClient;
        }

        else {
            int currentIndex = index;
            while( !clients_woReplacement[currentIndex].isEmpty() ) {
                currentIndex = (currentIndex + 1) % tableSize;
            }
            clients_woReplacement[currentIndex] = newClient;
        }
    }

    void insertClient_wReplacement( Client newClient ) {
        int index = hashfunction( newClient.name );
        if( clients_woReplacement[index].isEmpty() ) {
            clients_woReplacement[index] = newClient;
        }

        else {
            if( isOriginal(index) ) {
                int currentIndex = index;
                while( !clients_woReplacement[currentIndex].isEmpty() ) {
                    currentIndex = (currentIndex + 1) % tableSize;
                }
                clients_woReplacement[currentIndex] = newClient;
            }

            else {
                Client existingClient = clients_woReplacement[index];
                clients_woReplacement[index] = newClient;
                int currentIndex = index;
                while( !clients_woReplacement[currentIndex].isEmpty() ) {
                    currentIndex = (currentIndex + 1) % tableSize;
                }
                clients_woReplacement[currentIndex] = existingClient;
            }
        }
    }

    void search( char clientName[] ) {
        int index = hashfunction( clientName );
        if( strcmp( clientName, clients_woReplacement[index].name ) == 0) {
            clients_woReplacement[index].printDetails();
        }

        else {

            int currentIndex = index;
            int passes = 0;
            while( strcmp( clients_woReplacement[currentIndex].name, clientName ) != 0 and passes != tableSize ) {
                currentIndex = (currentIndex + 1) % tableSize;
                passes++;
            }

            if( passes != tableSize ) {
                clients_woReplacement[index].printDetails();
            }

            else {
                cout<<"No such client found"<<endl;
            }
        }
    }

    void displayHT() {
        cout.width( 20 ) ;
		cout << "Client Name  " ;
		cout.width( 20 ) ;
		cout << "Telephone  \n";
		for( int i = 0 ; i < (this->tableSize) ; i++ ) {
			clients_woReplacement[ i ].printDetails() ;
		}
    }
};


int main()
{
    int n;
    cout << "Enter number of clients: ";
    cin >> n;
    Hashtable table(n);
    table.createTable();
    for(int i = 0; i<n; i++) {
        cout << "Enter client name: ";
        char name[20];
        cin >> name;
        cout << "Enter client phone: ";
        ll phone;
        cin >> phone;
        Client newClient( name, phone );
        table.insertClient_woReplacement(newClient);
    }

    table.displayHT();

    return 0;
}
